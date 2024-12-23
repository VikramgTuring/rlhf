#include <iostream>
using namespace std;

// Helper function to calculate total size for N-dimensional arrays
template <int... Sizes>
constexpr int calculateTotalSize() {
    return (... * Sizes); // Fold expression to compute total size
}

// Recursive function to copy elements for N-dimensional arrays
template <typename T, int M, int... Sizes>
void cloneRecursive(const T (&original)[M][Sizes...], T* cloned, int& index) {
    for (int i = 0; i < M; ++i) {
        cloneRecursive(original[i], cloned, index); // Recursive call
    }
}

// Base case: Copying elements for 1D arrays
template <typename T, int M>
void cloneRecursive(const T (&original)[M], T* cloned, int& index) {
    for (int i = 0; i < M; ++i) {
        cloned[index++] = original[i];
    }
}

// Clone function for N-dimensional arrays
template <typename T, int... Sizes>
T* cloneArrayND(const T (&original)[Sizes...]) {
    constexpr int totalSize = calculateTotalSize<Sizes...>(); // Total size
    T* cloned = new T[totalSize];
    int index = 0;
    cloneRecursive(original, cloned, index); // Recursive cloning
    return cloned;
}

// Clone function for 1D arrays
template <typename T, int Size>
T* cloneArray1d(const T (&original)[Size]) {
    T* cloned = new T[Size];
    for (int i = 0; i < Size; ++i) {
        cloned[i] = original[i];
    }
    return cloned;
}

int main() {
    // 1D Array
    int originalIntArray[] = {1, 2, 3, 4, 5};
    int* clonedIntArray = cloneArray1d(originalIntArray);
    cout << "Cloned 1D Integer Array: ";
    for (int i = 0; i < 5; ++i) {
        cout << clonedIntArray[i] << " ";
    }
    cout << endl;
    delete[] clonedIntArray;

    // 2D Array
    int original2DArray[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int* cloned2DArray = cloneArrayND(original2DArray);
    cout << "Cloned 2D Integer Array: ";
    for (int i = 0; i < 6; ++i) {
        cout << cloned2DArray[i] << " ";
    }
    cout << endl;
    delete[] cloned2DArray;

    // 3D Array
    int original3DArray[2][2][2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    int* cloned3DArray = cloneArrayND(original3DArray);
    cout << "Cloned 3D Integer Array: ";
    for (int i = 0; i < 8; ++i) {
        cout << cloned3DArray[i] << " ";
    }
    cout << endl;
    delete[] cloned3DArray;

    return 0;
}

