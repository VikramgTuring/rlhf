#include <iostream>
#include <stdexcept>

template <typename T>
T* cloneArray(const T* original, size_t size) {
    if (original == nullptr || size == 0) {
        return nullptr; // Return nullptr for null or zero-size array
    }

    // Allocate a new array of the same size
    T* clonedArray = new T[size];
    
    // Copy elements from the original array to the cloned array
    for (size_t i = 0; i < size; ++i) {
        clonedArray[i] = original[i];
    }

    return clonedArray;
}

template <typename T>
void deleteArray(T* array) {
    delete[] array; // Deallocate the memory for the array
}

int main() {
    // Example usage with an integer array
    int originalIntArray[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(originalIntArray) / sizeof(originalIntArray[0]);

    int* clonedIntArray = cloneArray(originalIntArray, size);
    
    std::cout << "Cloned Integer Array: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << clonedIntArray[i] << " ";
    }
    std::cout << std::endl;

    deleteArray(clonedIntArray); // Clean up dynamically allocated memory

    // Example usage with a double array
    double originalDoubleArray[] = {1.1, 2.2, 3.3};
    size_t doubleSize = sizeof(originalDoubleArray) / sizeof(originalDoubleArray[0]);

    double* clonedDoubleArray = cloneArray(originalDoubleArray, doubleSize);
    
    std::cout << "Cloned Double Array: ";
    for (size_t i = 0; i < doubleSize; ++i) {
        std::cout << clonedDoubleArray[i] << " ";
    }
    std::cout << std::endl;

    deleteArray(clonedDoubleArray); // Clean up dynamically allocated memory

    return 0;
}
