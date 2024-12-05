#include <iostream>
#include <list>

int main() {
    std::list<int> myList = {1, 2, 3, 4, 5, 5, 6, 7};

    // Display the original list
    std::cout << "Original list: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Element to be removed
    int elementToRemove = 5;

    // Bidirectional iterators to traverse from both ends
    auto startIt = myList.begin();
    auto endIt = myList.end();
    --endIt; // Move the end iterator to the second last element

    while (startIt != endIt) {
        if (*startIt == elementToRemove) {
            myList.erase(startIt);
        } else if (*endIt == elementToRemove) {
            myList.erase(endIt);
        }
        ++startIt;
        --endIt;
    }

    // After removing the element, traverse the updated list
    std::cout << "Updated list after removing " << elementToRemove << ": ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}