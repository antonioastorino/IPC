#ifndef IPCTransmitter_hpp
#define IPCTransmitter_hpp
#include <cstdint>

namespace IPC {
class Transmitter {
private:
    Transmitter();

    uint8_t* buffer_;
    uint8_t* r_; // receiver's index (r stands for reader)
    uint8_t* w_; // transmitter's index (w stands for writer)

    static bool s_initialized_;

public:
    Transmitter(const char*, char);

    void run();
};
} // namespace IPC

#endif /* IPCTransmitter_hpp */