#include <iostream>
#include <cstdlib>

int main() {
    int* ptr = new int;
    *ptr = 42;

    // We forget to delete ptr, so this will cause a memory leak

    std::cout << "Program execution complete." << std::endl;
    return 0;
}
