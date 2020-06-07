#include "IPCTransmitter.hpp"
#include "BinaryMessageBuilder.hpp"
#include "HEGMap.hpp"


int main() {
    // ftok to generate unique key - make sure the file passed as parameter exists and is the same
    // in both transmitter and receiver
    IPC::Transmitter tx("../include/IPCCommon.hpp", 65);
    tx.run();

    return 0;
}