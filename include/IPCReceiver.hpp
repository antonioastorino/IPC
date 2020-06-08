#ifndef IPCReceiver_hpp
#define IPCReceiver_hpp
#include <cstdint>

namespace IPC {
class Receiver {
private:
    Receiver();

    uint8_t* buffer_;
    uint8_t* p_r_;
    uint8_t* p_w_;
    int shmid_;

    static bool s_initialized_;

public:
    Receiver(const char*, int);

    void run();
};
} // namespace IPC

#endif /* IPCReceiver_hpp */