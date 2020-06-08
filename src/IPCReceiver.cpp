#include "IPCReceiver.hpp"
#include "HEGEncoding.hpp"
#include "IPCCommon.hpp"
#include <sys/ioctl.h>

IPC::Receiver::Receiver(const char* filePath, int rxShmid) {
    if (Receiver::s_initialized_) throw "Receiver already initialized";
    Receiver::s_initialized_ = true;

    // ftok to generate unique key - make sure the file passed as parameter exists and is the
    // same
    // in both transmitter and receiver

    key_t key;
    char secretChar = 0;
    int flags       = 0666 | IPC_CREAT;

    if (rxShmid < 0) { flags |= IPC_EXCL; } // create a new shared memory if shmid is not specified

    while (rxShmid < 0) {
        key = ftok(filePath, (secretChar)++);
        // get shared memory ID based on the key and the desired buffer size
        if (key > -1) { rxShmid = shmget(key, IPC::bufferSize, flags); }
    }
    std::cout << "RX channel: " << rxShmid << std::endl;
    {
        std::ofstream f("shm-id");
        f << rxShmid;
        f.close();
    }

    // shmat to attach to shared memory
    this->shmid_  = rxShmid;
    this->buffer_ = (uint8_t*)shmat(shmid_, (void*)0, 0);
    this->r_      = &this->buffer_[IPC::bufferSize - 2];
    this->w_      = &this->buffer_[IPC::bufferSize - 1];
    *this->r_     = 0;
    *this->w_     = 0;
}

void IPC::Receiver::run() {
    // The following is be done in preparation for the transmission and could be skipped once
    // the encoding is established and saved.
    HEG::Encoding encoding("../assets/sample-text.txt");

    const char* encodingFileName = "../data/huffman-code.txt"; // TODO: define in a common file
    encoding.printEncoding(encodingFileName);

    std::vector<uint8_t> data;
    bool endOfTransmission = false;
    while (!endOfTransmission) { // keep reading until you hit the read location
        while (*this->w_ == *this->r_) {
            usleep(IPC::sleepTimeMicroSec);
            if (!data.empty()) {
                std::string receivedMsg = "";
                encoding.decode(data, 0, data.size() * sizeof(data[0]) * 8 - 1,
                                receivedMsg); // TODO: 8 is the number of bits per array element
                                              // and should be calculated/retrieved

                struct winsize size;
                ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); // get window size

                std::cout << std::setw(size.ws_col) << std::right << "Them (most likely you again)\n";
                std::cout << std::setw(size.ws_col) << std::right << receivedMsg << " ";
                std::cout.flush();

                // NOTE: the buffer size must be large enough to contain `\` and `\n` otherwise
                // the condition below will never be fulfilled
                if (receivedMsg[0] == IPC::terminationChar && receivedMsg[1] == '\n') {
                    endOfTransmission = true;
                    std::cout << "Termination character received\n";
                    break;
                }

                // for (auto it = data.begin(); it != data.end(); it ++) {
                //     std::cout << std::bitset<8>(*it);
                // }
                // std::cout << std::endl;
                data = {};
            }
            // std::cout << "Waiting for message... \n";
        }

        data.push_back(this->buffer_[*this->r_]);

        *this->r_ = (*this->r_ + 1) % (IPC::bufferSize - 2);
        // std::cout << "I'm done reading at location " << (int)*r << "\n";
    }

    // detach from shared memory
    shmdt(this->buffer_);

    // destroy the shared memory
    shmctl(this->shmid_, IPC_RMID, NULL);
}

bool IPC::Receiver::s_initialized_ = false;