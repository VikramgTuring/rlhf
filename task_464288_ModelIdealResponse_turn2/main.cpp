#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>
#include <concepts>

// Clone function using std::vector
template <typename T>
std::vector<T> cloneArray(const std::vector<T>& original) {
    return std::vector<T>(original); // Copy constructor for cloning
}

// Function template specialized for pointers
template <typename T>
std::enable_if_t<std::is_pointer_v<T>, std::vector<std::remove_pointer_t<T>>>
cloneArray(T original, size_t size) {
    using ElementType = std::remove_pointer_t<T>;
    std::vector<ElementType> cloned(size);

    // Copy elements from original
    for (size_t i = 0; i < size; ++i) {
        cloned[i] = original[i];
    }

    return cloned;
}

// Function template specialized for arrays
template <typename T, size_t N>
std::vector<T> cloneArray(const T (&original)[N]) {
    return std::vector<T>(original, original + N); // Copy elements to a vector
}

// Concept to validate clonable types
template <typename T>
concept Clonable = std::is_pointer_v<T> || requires(T a) {
    { std::vector<typename T::value_type>(a) }; // Valid for containers like std::vector
};

// Function that validates and calls the appropriate clone implementation
template <Clonable T>
auto clone(const T& original, size_t size = 0) {
    if constexpr (std::is_pointer_v<T>) {
        return cloneArray(original, size); // Call pointer-specific overload
    } else {
        return cloneArray(original); // Call vector overload
    }
}

// Overload for arrays
template <typename T, size_t N>
auto clone(const T (&original)[N]) {
    return cloneArray(original); // Call array-specific overload
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
    auto clonedArray = clone(originalArray);

    // Print cloned array
    std::cout << "Cloned Array: ";
    for (const auto& elem : clonedArray) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

