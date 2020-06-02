#include <iostream>
#include <stdio.h>
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
   
    while (true) { // keep reading until you hit the read location
        while (*w == *r) {
            usleep(100);
        }
        if (buffer[*r] == '\\') break;
        std::cout << buffer[*r];
        std::cout.flush();

        *r = (*r + 1) % (bufferSize - 2);
        // std::cout << "I'm done reading at location " << (int)*r << "\n";
        // sleep(1);
    }

    // detach from shared memory
    shmdt(buffer);

    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
