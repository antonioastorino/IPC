#include "BinaryMessageBuilder.hpp"
#include <iostream>

template <typename T>
std::vector<T> BinaryMessageBuilder::build(const std::string& message) {
    std::vector<T> ret_vector = {};
    if (message.size()) {
        uint8_t bitsPerElement   = sizeof(T) * 8;
        uint64_t totNumOfElements = (message.size() - 1) / bitsPerElement + 1;
        ret_vector.resize(totNumOfElements);
		uint64_t currElement;
		uint8_t currBit;
        for (size_t i = 0; i < message.size(); i++) {
			currElement = i / bitsPerElement;
			currBit = i % bitsPerElement;
			ret_vector[currElement] |= (message[i] == '0' ? 0 : 1) << currBit;
		}
    }
    return ret_vector;
}
template std::vector<uint8_t> BinaryMessageBuilder::build(const std::string& message);
template std::vector<uint16_t> BinaryMessageBuilder::build(const std::string& message);
template std::vector<uint32_t> BinaryMessageBuilder::build(const std::string& message);
template std::vector<uint64_t> BinaryMessageBuilder::build(const std::string& message);