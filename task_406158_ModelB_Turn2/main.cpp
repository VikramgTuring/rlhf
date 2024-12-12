#include <iostream>

int* allocateMemory() {
    return new int(42);
}

int main() {
    int* ptr = allocateMemory();
    // We forgot to delete[] ptr here, leading to a memory leak

    return 0;
}
