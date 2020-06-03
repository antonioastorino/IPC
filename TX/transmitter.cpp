#include <iostream>
#include <stdio.h>
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

    std::string inputStr;

    while (inputStr[0] != '\\') {
        // get input line by line
        std::cout << "Write Data : ";
        std::getline(std::cin, inputStr);
        uint16_t charLocation = 0;

        while (inputStr[charLocation] != 0) { // scan the string
            while (*w == ((*r) - 1) || *w == ((*r) + bufferSize - 3)) {
                // std::cout << "Waiting for the buffer to be read\n";
                usleep(10000);
            }; // wait if this is where the reader is located
            buffer[*w] = inputStr[charLocation];
            *w         = (*w + 1) % (bufferSize - 2);
            charLocation++;
        }

        // std::cout << "I'm done writing at location " << (int)*w << "\n";
    }

    printf("Termination character received\n");

    // detach from shared memory
    shmdt(buffer);

    return 0;
}