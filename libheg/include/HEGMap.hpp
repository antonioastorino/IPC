#ifndef HEGMap_hpp
#define HEGMap_hpp
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

namespace HEG {
class Map {
private:
    Map();
    std::unordered_map<char, std::string> mp_;

public:
    Map(const char*);
	std::string getCodeForSymbol(char);
};
} // namespace HEG

#endif /* HEGMap_hpp */
