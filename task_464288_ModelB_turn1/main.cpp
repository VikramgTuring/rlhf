#include <iostream>
using namespace std;

template <typename T>
T* cloneArray(const T* arr, size_t size) {
    T* clonedArray = new T[size];
    for (size_t i = 0; i < size; i++) {
        clonedArray[i] = arr[i];
    }
    return clonedArray;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int* clonedIntArray = cloneArray(arr, size);

    for (size_t i = 0; i < size; i++) {
        cout << "Cloned array element " << i << ": " << clonedIntArray[i] << endl;
    }

    // Remember to delete the cloned array to prevent memory leaks
    delete[] clonedIntArray;

    double arrDouble[] = {1.0, 2.5, 3.3};
    size_t sizeDouble = sizeof(arrDouble) / sizeof(arrDouble[0]);

    double* clonedDoubleArray = cloneArray(arrDouble, sizeDouble);

    for (size_t i = 0; i < sizeDouble; i++) {
        cout << "Cloned double array element " << i << ": " << clonedDoubleArray[i] << endl;
    }

    // Delete the cloned double array
    delete[] clonedDoubleArray;

    return 0;
}
