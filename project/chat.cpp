#include "HEGEncoding.hpp"
#include "IPCCommon.hpp"
#include "IPCReceiver.hpp"
#include "IPCTransmitter.hpp"
#include <fstream>
#include <sstream>
#include <thread>

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

    IPC::Receiver rx("../include/IPCCommon.hpp", rxShmid);
    IPC::Transmitter tx("../include/IPCCommon.hpp", txShmid);

    std::thread t_rx(&IPC::Receiver::run, &rx);
    std::thread t_tx(&IPC::Transmitter::run, &tx);

    t_rx.join();
    t_tx.join();

    std::ofstream f("shm-id");
    f << "";
    f.close();
    return 0;
}
