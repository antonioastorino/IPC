#include "HEGEncoding.hpp"
#include "IPCCommon.hpp"
#include "IPCReceiver.hpp"
#include "IPCTransmitter.hpp"
#include <thread>

int main() {
    IPC::Receiver rx("../include/IPCCommon.hpp", 65);
    IPC::Transmitter tx("../include/IPCCommon.hpp", 66);

    std::thread t_rx(&IPC::Receiver::run, &rx);
    std::thread t_tx(&IPC::Transmitter::run, &tx);

    t_rx.join();
    t_tx.join();

    return 0;
}
