#include "BinaryMessageBuilder.hpp"
#include "HEGMap.hpp"
#include <iostream>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    // ftok to generate unique key
    key_t key                 = ftok("shmfile", 65);
    const uint16_t bufferSize = 256;

    // shmget returns an identifier in shmid
    int shmid = shmget(key, bufferSize, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    uint8_t* buffer = (uint8_t*)shmat(shmid, (void*)0, 0);
    uint8_t* r      = &buffer[bufferSize - 2];
    uint8_t* w      = &buffer[bufferSize - 1];
    *r              = 0;
    *w              = 0;

    std::string clearMsg;
    std::cout << "Loading encoded alphabet from file...\n";
    const char* encodingFileName = "../data/huffman-code.txt";
    HEG::Map mp(encodingFileName);

    std::cout << "Done!\n";

    while (clearMsg[0] != '\\') {
        // get input line by line
        std::cout << "Transmig Data : ";
        std::getline(std::cin, clearMsg);

        std::string encodedMsg = ""; // Encoded message - not yet suitable for transmission
        for (size_t i = 0; i < clearMsg.size(); i++) {
            encodedMsg += mp.getCodeForSymbol(clearMsg[i]); // Huffman's encoding for each character
            // std::cout << mp.getCodeForSymbol(clearMsg[i]) << std::endl;
        }
        // at this point, encodedMsg is a string of `0`'s and `1`'s. We want these `0`'s and `1`'s
        // to be converted into actual bits in the binary message

        // convert string into binary sequence - message suitable for transmission
        std::vector<uint8_t> data = BinaryMessageBuilder::build<uint8_t>(encodedMsg);

        for (size_t dataIndex = 0; dataIndex < data.size(); dataIndex++) { // scan the string
            while (*w == ((*r) - 1) || *w == ((*r) + bufferSize - 3)) {
                // std::cout << "Waiting for the buffer to be read\n";
                usleep(10000);
            }; // wait if this is where the reader is located
            buffer[*w] = data[dataIndex];
            *w         = (*w + 1) % (bufferSize - 2);
        }

        // std::cout << "I'm done writing at location " << (int)*w << "\n";
    }

    std::cout << "Termination character received\n";

    // detach from shared memory
    shmdt(buffer);

    return 0;
}