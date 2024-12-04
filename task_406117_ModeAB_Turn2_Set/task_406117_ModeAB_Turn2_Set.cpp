#include <iostream>
#include <set>

int main() {
    std::set<int> mySet;
    mySet.insert(1);
    mySet.insert(8);
    mySet.insert(4);
    mySet.insert(2);
    mySet.insert(5);

    std::cout << "Forward Iteration through std::set:\n";
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        std::cout << *it << std::endl;
    }

    std::cout << "\nReverse Iteration through std::set:\n";
    for (auto it = mySet.rbegin(); it != mySet.rend(); ++it) {
        std::cout << *it << std::endl;
    }

    return 0;
}