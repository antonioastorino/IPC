#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    char* str = (char*)shmat(shmid, (void*)0, 0);

    const char *cstr;

    std::string str1;

    while (str1[0] != '\\') {
        std::cout << "Write Data : ";
        std::getline(std::cin, str1);
        cstr = str1.c_str();
        std::memcpy(str, cstr, str1.size());
        str[str1.size()] = '\0'; 
    }

    printf("Termination character received: %s\n", str);

    // detach from shared memory
    shmdt(str);

    return 0;
}