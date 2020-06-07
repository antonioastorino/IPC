#include "HEGEncoding.hpp"
#include "IPCConstants.hpp"
#include <bitset>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <vector>

namespace IPC {
class Receiver {
private:
    Receiver();

    uint8_t* buffer_;
    uint8_t* r_;
    uint8_t* w_;
    int shmid_;

    static bool s_initialized_;

public:
    Receiver(const char* filePath, char secretChar) {
        if (Receiver::s_initialized_) throw "Receiver already initialized";
        Receiver::s_initialized_ = true;

        // ftok to generate unique key - make sure the file passed as parameter exists and is the
        // same
        // in both transmitter and receiver
        key_t key = ftok(filePath, secretChar);

        // get shared memory ID based on the key and the desired buffer size
        this->shmid_ = shmget(key, IPC::bufferSize, 0666 | IPC_CREAT);

        // shmat to attach to shared memory
        this->buffer_ = (uint8_t*)shmat(shmid_, (void*)0, 0);
        this->r_      = &this->buffer_[IPC::bufferSize - 2];
        this->w_      = &this->buffer_[IPC::bufferSize - 1];
        *this->r_     = 0;
        *this->w_     = 0;
    }

    void run() {
        // The following is be done in preparation for the transmission and could be skipped once
        // the encoding is established and saved.
        std::cout << "Creating encoding based on the content of a file...\n";
        HEG::Encoding encoding("../assets/sample-text.txt");
        std::cout << "Done!\n\n";

        std::cout << "Printing encoded alphabet to file...\n";
        const char* encodingFileName = "../data/huffman-code.txt"; // TODO: define in a common file
        encoding.printEncoding(encodingFileName);
        std::cout << "Done!\n\n";
        std::cout << "\nTransmission started. Waiting for incoming messages...\n";

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
                    std::cout << "Received message: " << receivedMsg;
                    std::cout.flush();

                    // NOTE: the buffer size must be large enough to contain `\` and `\n` otherwise
                    // the condition below will never be fulfilled
                    if (receivedMsg[0] == IPC::terminationChar && receivedMsg[1] == '\n') {
                        endOfTransmission = true;
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
};
} // namespace IPC

bool IPC::Receiver::s_initialized_ = false;

int main() {
    IPC::Receiver rx("../include/IPCConstants.hpp", 65);
    rx.run();

    return 0;
}
