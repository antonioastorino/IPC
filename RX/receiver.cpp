#include "HEGEncoding.hpp"
#include "IPCCommon.hpp"
#include "IPCReceiver.hpp"

int main() {
    IPC::Receiver rx("../include/IPCCommon.hpp", 65);
    rx.run();

    return 0;
}
