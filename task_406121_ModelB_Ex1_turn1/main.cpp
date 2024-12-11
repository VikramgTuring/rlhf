
#include <iostream>

int main() {
    char buffer[10];

    std::cout << "Enter a string: ";
    std::cin.getline(buffer, 20); // Buffer overflow vulnerability here

    std::cout << "You entered: " << buffer << std::endl;

    return 0;
}
