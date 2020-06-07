#include "HEGEncoding.hpp"
#include "IPCConstants.hpp"
#include <bitset>
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <vector>

int main() {
    // ftok to generate unique key - make sure the file passed as parameter exists and is the same
    // in both transmitter and receiver
    key_t key = ftok("../include/IPCConstants.hpp", 65);

    // get shared memory ID based on the key and the desired buffer size
    int shmid = shmget(key, IPC::bufferSize, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    uint8_t* buffer = (uint8_t*)shmat(shmid, (void*)0, 0);
    uint8_t* r      = &buffer[IPC::bufferSize - 2];
    uint8_t* w      = &buffer[IPC::bufferSize - 1];
    *r              = 0;
    *w              = 0;

    // The following is be done in preparation for the transmission and could be skipped once the
    // encoding is established and saved.
    std::cout << "Creating encoding based on the content of a file...\n";
    HEG::Encoding encoding("../assets/sample-text.txt");
    std::cout << "Done!\n";

    std::cout << "Printing encoded alphabet to file...\n";
    const char* encodingFileName = "../data/huffman-code.txt"; // TODO: define in a common file
    encoding.printEncoding(encodingFileName);
    std::cout << "Done!\n";

    std::vector<uint8_t> data;
    bool endOfTransmission = false;
    while (!endOfTransmission) { // keep reading until you hit the read location
        while (*w == *r) {
            usleep(IPC::sleepTimeMicroSec);
            if (!data.empty()) {
                std::string receivedMsg = "";
                encoding.decode(data, 0, data.size() * sizeof(data[0]) * 8 - 1,
                                receivedMsg); // TODO: 8 is the number of bits per array element and
                                              // should be calculated/retrieved
                std::cout << receivedMsg;
                std::cout.flush();

                // NOTE: the buffer size must be large enough to contain `\` and `\n` otherwise the
                // condition below will never be fulfilled
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

        data.push_back(buffer[*r]);

        *r = (*r + 1) % (IPC::bufferSize - 2);
        // std::cout << "I'm done reading at location " << (int)*r << "\n";
    }

    // detach from shared memory
    shmdt(buffer);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
