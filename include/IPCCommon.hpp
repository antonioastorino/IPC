#ifndef IPCCommon_hpp
#define IPCCommon_hpp
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <vector>
#include <unistd.h>


namespace IPC {
constexpr uint64_t bufferSize        = 200;
constexpr uint32_t sleepTimeMicroSec = 1000;
constexpr uint8_t terminationChar    = '\\';

} // namespace IPC

#endif /* IPCCommon_hpp */