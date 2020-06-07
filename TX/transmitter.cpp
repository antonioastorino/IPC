#include "HEGEncoding.hpp"
#include "IPCCommon.hpp"
#include "IPCReceiver.hpp"
#include "IPCTransmitter.hpp"
#include <thread>

int main() {
    IPC::Transmitter tx("../include/IPCCommon.hpp", 65);
    IPC::Receiver rx("../include/IPCCommon.hpp", 66);

    std::thread t_tx(&IPC::Transmitter::run, &tx);
    std::thread t_rx(&IPC::Receiver::run, &rx);

    t_tx.join();
    t_rx.join();

    return 0;
}