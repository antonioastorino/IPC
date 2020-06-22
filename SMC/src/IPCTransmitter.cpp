#include "SMCTransmitter.hpp"
#include "BinaryMessageBuilder.hpp"
#include "HEGMap.hpp"
#include "SMCCommon.hpp"
#include <string>

SMC::Transmitter::Transmitter(const char* filePath, int txShmid) {

    if (SMC::Transmitter::s_initialized_) throw "Transmitter already initialized";
    Transmitter::s_initialized_ = true;

    key_t key;
    char secretChar = 0;
    int flags       = 0666 | IPC_CREAT;

    if (txShmid < 0) { flags |= IPC_EXCL; } // create a new shared memory if shmid is not specified

    while (txShmid < 0) {
        key = ftok(filePath, (secretChar)++);
        // get shared memory ID based on the key and the desired buffer size
        if (key > -1) { txShmid = shmget(key, SMC::bufferSize, flags); }
    }
    std::cout << "TX channel: " << txShmid << std::endl;
    {
        std::ofstream f("shm-id", std::ios::app);
        f << " " << txShmid;
        f.close();
    }
    // shmat to attach to shared memory
    this->buffer_ = (uint8_t*)shmat(txShmid, (void*)0, 0);
    this->p_r_      = &buffer_[SMC::bufferSize - 2]; // second last element's location
    this->p_w_      = &buffer_[SMC::bufferSize - 1]; // last element's location
    *this->p_r_     = 0;
    *this->p_w_     = 0;
}

void SMC::Transmitter::run() {
    std::string clearMsg;
    const char* encodingFileName = "data/huffman-code.txt";
    HEG::Map mp(encodingFileName);

    while (!(clearMsg[0] == SMC::terminationChar && clearMsg[1] == '\n')) {
        // get input line by line
        std::cout << "You\n ";
        std::getline(std::cin, clearMsg);
        clearMsg += '\n';

        std::string encodedMsg = ""; // Encoded message - not yet suitable for transmission
        for (size_t i = 0; i < clearMsg.size(); i++) {
            encodedMsg += mp.getCodeForSymbol(clearMsg[i]); // Huffman's encoding for each character
            // std::cout << mp.getCodeForSymbol(clearMsg[i]) << std::endl;
        }
        // at this point, encodedMsg is a string of `0`'s and `1`'s. We want these `0`'s and
        // `1`'s to be converted into actual bits in the binary message std::cout << "encoded
        // message: " << encodedMsg << "\n"; convert string into binary sequence - message
        // suitable for transmission
        std::vector<uint8_t> data = BinaryMessageBuilder::build<uint8_t>(encodedMsg);

        for (size_t dataIndex = 0; dataIndex < data.size(); dataIndex++) { // scan the string
            buffer_[*this->p_w_] = data[dataIndex];
            while (*this->p_w_ == ((*this->p_r_) - 1)
                   || *this->p_w_ == ((*this->p_r_) + SMC::bufferSize - 3)) {
                // std::cout << "Waiting for the buffer to be read\n";
                usleep(SMC::sleepTimeMicroSec);
            }; // wait if this is where the reader is located
            *this->p_w_ = (*this->p_w_ + 1) % (SMC::bufferSize - 2);
        }

        // std::cout << "I'm done writing at location " << (int)*w << "\n";
    }

    std::cout << "Termination character sent\n";

    // detach from shared memory
    shmdt(this->buffer_);
}

bool SMC::Transmitter::s_initialized_ = false;