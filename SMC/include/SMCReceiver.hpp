#ifndef SMCReceiver_hpp
#define SMCReceiver_hpp
#include <cstdint>

namespace SMC {
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
} // namespace SMC

#endif /* SMCReceiver_hpp */