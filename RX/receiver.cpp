#include "HEGEncoding.hpp"
#include "IPCConstants.hpp"
#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <vector>
#include <bitset>

int main() {
    // ftok to generate unique key
    key_t key                 = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, BUFFER_SIZE, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    uint8_t* buffer = (uint8_t*)shmat(shmid, (void*)0, 0);
    uint8_t* r      = &buffer[BUFFER_SIZE - 2];
    uint8_t* w      = &buffer[BUFFER_SIZE - 1];
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
            usleep(10000);
            if (!data.empty()) {
                std::string receivedMsg = "";
                encoding.decode(data, 0, data.size() * sizeof(data[0]) * 8 - 1,
                                receivedMsg); // TODO: 8 is the number of bits per array element and
                                              // should be calculated/retrieved
                if (receivedMsg[0] == '\\') {
                    endOfTransmission = true;
                    break;
                }
                std::cout << receivedMsg;
                std::cout.flush();
                // for (auto it = data.begin(); it != data.end(); it ++) {
                //     std::cout << std::bitset<8>(*it);
                // }
                // std::cout << std::endl;
                data = {};
            }
            // std::cout << "Waiting for message... \n";
        }

        data.push_back(buffer[*r]);

        *r = (*r + 1) % (BUFFER_SIZE - 2);
        // std::cout << "I'm done reading at location " << (int)*r << "\n";
    }

    // detach from shared memory
    shmdt(buffer);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
