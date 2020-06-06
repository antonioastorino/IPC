#ifndef BinaryMessageBuilder_hpp
#define BinaryMessageBuilder_hpp
#include <vector>
#include <string>


/** 
 * @class BinaryMessageBuilder
 * creates a stream of bits matching the string of `0`'s and `1`'s used for creating the message. For example, supposing to have a the following:
 * 
 * ```
 * std::string message = "0001" "00001" "01"
 * auto v = BinaryMessageBuilder::build<uint8_t>(message);
 * ```
 * returns a vector `v` of 2 elements:
 * - v[0] = 0b00010000
 * - v[1] = 0b10100000
 * 
 * Notice that the second element is zero-padded
 */
class BinaryMessageBuilder {
public:
template<typename T>
static std::vector<T> build(const std::string &message); 
};

#endif /*BinaryMessageBuilder_hpp*/