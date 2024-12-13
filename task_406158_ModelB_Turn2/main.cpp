#include <cstdlib> // For malloc/free
#include <iostream>

int main() {
    void* ptr = malloc(100);
    // We forgot to free the allocated memory

    // Comment out the following line to see the leak report
    // free(ptr);

    std::cout << "Program execution complete." << std::endl;
    return 0;
}
