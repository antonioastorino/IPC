#include <iostream>
#include <string.h>

namespace TCP
{
void error(std::string message) { std::cerr << "\033[40m" << message << "\033[0m\n"; }

void info(std::string message) { std::cout << "\033[33m" << message << "\033[0m\n"; }

void print(std::string message) { std::cout << "\033[0mMessage:       " << message << "\033[0m\n"; }
} // namespace TCP