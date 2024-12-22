#include <iostream>
#include <cstdlib> // For std::malloc and std::free

template <typename T>
T* cloneArray(const T* array, size_t size) {
    T* clonedArray = static_cast<T*>(std::malloc(size * sizeof(T)));

    if (clonedArray == nullptr) {
        std::cerr << "Memory allocation failed." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::memcpy(clonedArray, array, size * sizeof(T));

    return clonedArray;
}

template <typename T>
void deleteArray(T* array) {
    std::free(array);
}

int main() {
    // Example with integers
    int arr[] = {1, 2, 3, 4, 5};
    size_t arrSize = sizeof(arr) / sizeof(arr[0]);

    int* clonedIntArray = cloneArray(arr, arrSize);

    for (size_t i = 0; i < arrSize; i++) {
        std::cout << "Cloned integer array: " << clonedIntArray[i] << std::endl;
    }

    deleteArray(clonedIntArray);

    // Example with doubles
    double doubleArr[] = {1.1, 2.2, 3.3, 4.4};
    size_t doubleArrSize = sizeof(doubleArr) / sizeof(doubleArr[0]);

    double* clonedDoubleArray = cloneArray(doubleArr, doubleArrSize);

    for (size_t i = 0; i < doubleArrSize; i++) {
        std::cout << "Cloned double array: " << clonedDoubleArray[i] << std::endl;
    }

    deleteArray(clonedDoubleArray);

    return 0;
}
