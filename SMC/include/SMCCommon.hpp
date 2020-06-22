#ifndef SMCCommon_hpp
#define SMCCommon_hpp
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <vector>
#include <unistd.h>
#include <fstream>

namespace SMC {
constexpr uint64_t bufferSize        = 200;
constexpr uint32_t sleepTimeMicroSec = 1000;
constexpr uint8_t terminationChar    = '\\';

} // namespace SMC

#endif /* SMCCommon_hpp */