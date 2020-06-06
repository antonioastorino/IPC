#ifndef HEGLog_hpp
#define HEGLog_hpp
// clang-format off
#define RELEASE 0
#define INFO 	1
#define DEBUG 	2
// clang-format on

#define LOG_LEVEL RELEASE

namespace HEG {
class Logger {
public:
static void error(const char *);
static void info(const char *);
static void debug(const char *);
	
};
} // namespace HEG

#endif