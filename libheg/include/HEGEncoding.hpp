#ifndef HEGEncoding_hpp
#define HEGEncoding_hpp
#include "HEGDataTypes.hpp"
#include <string>

namespace HEG {

class Encoding {
private:
    Encoding();

    alphabet_t alphabet_;                  // symbols and frequencies
    HuffmanEncoding tree_;                 // entry point to the encoding tree
    std::vector<HuffmanEncoding*> leaves_; // leaves of the tree
    std::vector<HuffmanEncoding*> nodes_;  // nodes of the tree

    void makeSymbolFrequencyTable(const char* filename);
    void makeTree(const std::vector<HuffmanEncoding*>&);
    void printTree(const HuffmanEncoding* tree, std::string code, std::ostream&);
    std::string charToString(uint8_t);

public:
    Encoding(const char*);
    ~Encoding();
    alphabet_t getAlphabet() const;

    // Read through the alphabet and print each symbol and corresponding freqency
    void printAlphabet();

    // Scan the tree using DFS and print a "0" for each left node and "1" for each right node.
    // Return when you hit the bottom. Prints to file if a file name is specified
    void printEncoding(const char* outFileName = "");
    template <typename T> 
    void decode(const std::vector<T>&, size_t, size_t, std::string&);
};

} // namespace HEG

#endif /* HEGEncoding_hpp */