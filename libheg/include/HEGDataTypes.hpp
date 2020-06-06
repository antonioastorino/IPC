#ifndef HEGDataTypes_hpp
#define HEGDataTypes_hpp
#include <vector>

typedef std::pair<uint8_t, uint64_t> symbol_t;
typedef std::vector<symbol_t> alphabet_t;

struct HuffmanEncoding {
    long int index         = -1;
    float freq             = 0;
    HuffmanEncoding* left  = nullptr;
    HuffmanEncoding* right = nullptr;
};

#endif /* HEGDataTypes_hpp */