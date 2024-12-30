#include <iostream>

// Replace #define with const and constexpr
constexpr double PI = 3.14159;       // Compile-time constant
constexpr int MAX_LENGTH = 100;       // Compile-time constant
constexpr int ARRAY_SIZE = 10;         // Compile-time constant

int main() {
    double circleArea = PI * 5 * 5;    // Area of a circle with radius 5
    int arr[ARRAY_SIZE];                // Use of constexpr for array size

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = i * 2;
    }
    
    std::cout << "Circle Area: " << circleArea << std::endl;
    std::cout << "Array Size: " << sizeof(arr) / sizeof(arr[0]) << std::endl;
    return 0;
}
