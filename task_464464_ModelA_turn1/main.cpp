#include <iostream>
#include <cstdint> // for uint32_t

// Function to demonstrate secure multi-party computation using bitwise operations
void secureComputation(uint32_t partyA_input, uint32_t partyB_input) {
    // Performing a bitwise AND operation
    uint32_t and_result = partyA_input & partyB_input;

    // Performing a bitwise OR operation
    uint32_t or_result = partyA_input | partyB_input;

    // Outputting the results of AND and OR operations
    std::cout << "Party A Input: " << std::bitset<32>(partyA_input) << " (" << partyA_input << ")\n";
    std::cout << "Party B Input: " << std::bitset<32>(partyB_input) << " (" << partyB_input << ")\n";
    std::cout << "AND Result: " << std::bitset<32>(and_result) << " (" << and_result << ")\n";
    std::cout << "OR Result: " << std::bitset<32>(or_result) << " (" << or_result << ")\n";
}

int main() {
    // Party A's private input (example)
    uint32_t partyA_input = 0b1101; // Binary representation (13 in decimal)
    
    // Party B's private input (example)
    uint32_t partyB_input = 0b1011; // Binary representation (11 in decimal)

    // Running the secure computation demonstration
    secureComputation(partyA_input, partyB_input);
    
    return 0;
}
