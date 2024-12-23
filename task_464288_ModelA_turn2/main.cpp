#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>

// Clone function using std::vector
template<typename T>
std::vector<T> cloneArray(const std::vector<T>& original) {
    // Use std::vector's copy constructor for cloning
    return std::vector<T>(original);
}

// Function template specialized for pointers
template<typename T>
std::enable_if_t<std::is_pointer_v<T>, std::vector<std::remove_pointer_t<T>>> 
cloneArray(T* original, size_t size) {
    using ElementType = std::remove_pointer_t<T>;
    std::vector<ElementType> cloned(size);

    // Copy elements from original
    for (size_t i = 0; i < size; ++i) {
        cloned[i] = original[i];
    }
    
    return cloned;
}

// Validates the array with Concepts (C++20 version for validation and better type restriction)
template <typename T>
concept Clonable = requires(T a) {
    { std::remove_pointer_t<std::decay_t<T>>{} };
};

// Conceptually validate before calling the clone function
template<Clonable T>
std::vector<std::remove_pointer_t<T>> clone(T original, size_t size) {
    if constexpr (std::is_pointer_v<T>) {
        return cloneArray(original, size); // Call pointer-specific overload
    } else {
        return cloneArray(original）； // Call vector overload
    }
}

int main() {
    // Example of cloning a vector of integers
    std::vector<int> originalVector = {1, 2, 3, 4, 5};
    auto clonedVector = clone(originalVector);

    // Print cloned vector
    std::cout << "Cloned Vector: ";
    for (const auto& elem : clonedVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Example of cloning a C-style array
    int originalArray[] = {6, 7, 8, 9, 10};
    size_t arraySize = sizeof(originalArray) / sizeof(originalArray[0]);

    auto clonedArray = clone(originalArray, arraySize);

    // Print cloned array
    std::cout << "Cloned Array: ";
    for (const auto& elem : clonedArray) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
