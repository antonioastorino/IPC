#include "HEGLog.hpp"
#include <iostream>

namespace HEG {

void Logger::error(const char* msg) { std::cerr << "HEG_ERROR: " << msg << "\n"; }

void Logger::info(const char* msg) {
#if LOG_LEVEL >= INFO
    std::cout << "HEG_INFO: " << msg << "\n";
#endif
}

void Logger::debug(const char* msg) {
#if LOG_LEVEL >= DEBUG
    std::cerr << "HEG_DEBUG: " << msg << "\n";
#endif
}

} // namespace HEG