#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iterator>

int main() {
    {
        // Example with std::vector
        std::vector<int> myVector = { 1, 2, 3, 4, 10, 18 };

        std::cout << "\nstd::vector example:\n";

        // Forward iteration
        std::cout << "Forward iteration: \n";
        for (auto it = myVector.begin(); it != myVector.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";

        // Reverse iteration
        std::cout << "Reverse iteration: \n";
        for (auto rit = myVector.rbegin(); rit != myVector.rend(); ++rit) {
            std::cout << *rit << " ";
        }
        std::cout << "\n";
    }

    {
        // Example with std::list
        std::list<std::string> myList = { "apple", "banana", "orange", "grape" };

        std::cout << "\nstd::list example:\n";

        // Forward iteration
        std::cout << "Forward iteration: \n";
        for (auto it = myList.begin(); it != myList.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";

        // Reverse iteration
        std::cout << "Reverse iteration: \n";
        for (auto rit = myList.rbegin(); rit != myList.rend(); ++rit) {
            std::cout << *rit << " ";
        }
        std::cout << "\n";
    }

    return 0;
}