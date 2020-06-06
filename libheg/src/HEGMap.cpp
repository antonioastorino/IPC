#include "HEGMap.hpp"

HEG::Map::Map(const char* filename) {
    std::string s = "";
    char c;
    int numOfChars = 0;

    // open file for reading
    std::ifstream file(filename);
    // Measure the length of the file and copy to string
    while (file.get(c)) {
        numOfChars++;
        s += c;
    };
    file.close();

	// Populate map
    int i = 0;
    while (s[i] != 0) {
        std::string code = "";
        while (s[i] != 32) { // space-separator
            code += s[i];
            i++;
        }
        i++; // skip the space
        char symbol = 0;
        while (s[i] != '\n') { // eol-separator
            symbol *= 10;      // shift by 4 bits
            symbol += (s[i] - 48);
            i++;
        }
        mp_[symbol] = code;
        i++;
    }
}

std::string HEG::Map::getCodeForSymbol(char symbol) {
	return mp_[symbol];
}

