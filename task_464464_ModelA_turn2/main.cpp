#include <iostream>
#include <string>
#include <cstdint>

uint32_t simple_hash(uint32_t input) {
    // Bitwise operations to manipulate input
    input = (input ^ 0x5A5A5A5A); // XOR with a constant
    input = (input << 13) | (input >> (32 - 13)); // Rotate left
    input = (input & 0xFFFFFFFF) + 0x12345678; // AND and add constant
    input = (input ^ (input >> 17)); // XOR with a right shift
    return input;
}

int main() {
    std::string data = "Hello, Blockchain!";
    uint32_t hash_value = simple_hash(static_cast<uint32_t>(std::hash<std::string>{}(data)));

    std::cout << "Original data: " << data << std::endl;
    std::cout << "Hash value: " << std::hex << hash_value << std::dec << std::endl;

    return 0;
}
