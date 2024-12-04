#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;
    myMap[1] = "Apple";
    myMap[2] = "Banana";
    myMap[3] = "Orange";
    myMap[4] = "Pineapple";

    std::cout << "Forward Iteration through std::map:\n";
    for (auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    std::cout << "\nReverse Iteration through std::map:\n";
    for (auto it = myMap.rbegin(); it != myMap.rend(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    return 0;
}