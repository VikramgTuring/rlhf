// main.cpp
#include <iostream>
#include "constants.h"

int main() {
    std::cout << "PI: " << Constants::PI << std::endl;
    std::cout << "Max Buffer Size: " << Constants::MAX_BUFFER_SIZE << std::endl;

    // Access old defines if still needed
    std::cout << "Old PI: " << PI_OLD << std::endl;
    std::cout << "Old Max Buffer Size: " << MAX_BUFFER_SIZE_OLD << std::endl;

    return 0;
}
