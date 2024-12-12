#include <iostream>
using namespace std;

class MemoryLeakExample {
public:
    MemoryLeakExample() {
        data = new int[1000]; // Dynamically allocating memory
    }

    ~MemoryLeakExample() {
        // We forgot to delete[] the allocated memory, leading to a leak
    }

private:
    int* data;
};

int main() {
    MemoryLeakExample* example = new MemoryLeakExample(); // Creating an object on the heap
    delete example; // Freeing the object but not the dynamically allocated memory
    return 0;
}

