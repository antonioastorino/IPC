#include "IPCTransmitter.hpp"
#include "BinaryMessageBuilder.hpp"
#include "HEGMap.hpp"
#include "IPCCommon.hpp"
#include <string>

IPC::Transmitter::Transmitter(const char* filePath, char secretChar) {

    if (IPC::Transmitter::s_initialized_) throw "Transmitter already initialized";
    Transmitter::s_initialized_ = true;
    key_t key                   = ftok(filePath, secretChar);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, IPC::bufferSize, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    this->buffer_ = (uint8_t*)shmat(shmid, (void*)0, 0);
    this->r_      = &buffer_[IPC::bufferSize - 2]; // second last element's location
    this->w_      = &buffer_[IPC::bufferSize - 1]; // last element's location
    *this->r_     = 0;
    *this->w_     = 0;
}

void IPC::Transmitter::run() {
    std::string clearMsg;
    std::cout << "Loading encoded alphabet from file...\n";
    const char* encodingFileName = "../data/huffman-code.txt";
    HEG::Map mp(encodingFileName);

    std::cout << "Done!\n\n";

    while (!(clearMsg[0] == IPC::terminationChar && clearMsg[1] == '\n')) {
        // get input line by line
        std::cout << "Data to transmit: ";
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
            buffer_[*this->w_] = data[dataIndex];
            while (*this->w_ == ((*this->r_) - 1)
                   || *this->w_ == ((*this->r_) + IPC::bufferSize - 3)) {
                // std::cout << "Waiting for the buffer to be read\n";
                usleep(IPC::sleepTimeMicroSec);
            }; // wait if this is where the reader is located
            *this->w_ = (*this->w_ + 1) % (IPC::bufferSize - 2);
        }

        // std::cout << "I'm done writing at location " << (int)*w << "\n";
    }

    std::cout << "Termination character received\n";

    // detach from shared memory
    shmdt(this->buffer_);
}

bool IPC::Transmitter::s_initialized_ = false;