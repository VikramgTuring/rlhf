// Header file (constants.h)
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <limits>

namespace Constants {
    constexpr double PI = 3.14159; // Compile-time constant
    constexpr size_t MAX_BUFFER_SIZE = 1024; // Compile-time constant

    // Backward compatibility
    #define PI_OLD PI
    #define MAX_BUFFER_SIZE_OLD MAX_BUFFER_SIZE
}

#endif // CONSTANTS_H
