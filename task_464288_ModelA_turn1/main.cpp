#include <iostream>

template<typename T>
T* cloneArray(const T* original, size_t size) {
    // Allocate memory for the new array
    T* cloned = new T[size];
    
    // Copy elements from the original array to the new array
    for (size_t i = 0; i < size; ++i) {
        cloned[i] = original[i];
    }
    
    return cloned; // Return the cloned array
}

int main() {
    // Example with an array of integers
    int originalIntArray[] = {1, 2, 3, 4, 5};
    size_t intArraySize = sizeof(originalIntArray) / sizeof(originalIntArray[0]);

    // Use cloneArray to create a clone of the integer array
    int* clonedIntArray = cloneArray(originalIntArray, intArraySize);

    // Print cloned integer array
    std::cout << "Cloned Integer Array: ";
    for (size_t i = 0; i < intArraySize; ++i) {
        std::cout << clonedIntArray[i] << " ";
    }
    std::cout << std::endl;

    // Clean up the allocated memory
    delete[] clonedIntArray;

    // Example with an array of doubles
    double originalDoubleArray[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    size_t doubleArraySize = sizeof(originalDoubleArray) / sizeof(originalDoubleArray[0]);

    // Use cloneArray to create a clone of the double array
    double* clonedDoubleArray = cloneArray(originalDoubleArray, doubleArraySize);

    // Print cloned double array
    std::cout << "Cloned Double Array: ";
    for (size_t i = 0; i < doubleArraySize; ++i) {
        std::cout << clonedDoubleArray[i] << " ";
    }
    std::cout << std::endl;

    // Clean up the allocated memory
    delete[] clonedDoubleArray;

    return 0;
}
