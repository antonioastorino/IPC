#include "HEGEncoding.hpp"
#include "SMCCommon.hpp"
#include "SMCReceiver.hpp"
#include "SMCTransmitter.hpp"
#include <fstream>
#include <sstream>
#include <thread>
#include <stdlib.h>

int main() {
    int rxShmid;
    int txShmid;
    {
        std::ifstream f("shm-id");
        std::string line;
        std::getline(f, line);
        std::istringstream iss(line);
        if (!(iss >> txShmid >> rxShmid)) {
            rxShmid = -1;
            txShmid = -1;
        }
    }

    SMC::Receiver rx("include/SMCCommon.hpp", rxShmid);
    SMC::Transmitter tx("include/SMCCommon.hpp", txShmid);
    std::system("clear");

    std::thread t_rx(&SMC::Receiver::run, &rx);
    std::thread t_tx(&SMC::Transmitter::run, &tx);

    t_rx.join();
    t_tx.join();

    std::ofstream f("shm-id");
    f << "";
    f.close();
    return 0;
}
