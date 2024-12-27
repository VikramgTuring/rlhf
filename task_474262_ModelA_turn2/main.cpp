#include <iostream>
#include <vector>
#include <unordered_set>

std::unordered_set<int> findUniqueMatches(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Step 1: Insert all elements of list1 into an unordered_set for fast lookup
    std::unordered_set<int> setList1(list1.begin(), list1.end());
    
    // Step 2: Create a set to hold unique matches
    std::unordered_set<int> uniqueMatches;

    // Step 3: Iterate over list2 and check if each element exists in setList1
    for (const int& item : list2) {
        if (setList1.find(item) != setList1.end()) {
            uniqueMatches.insert(item);  // Insert the matching item into uniqueMatches
        }
    }
    
    return uniqueMatches;  // Return the set of unique matches
}

int main() {
    std::vector<int> list1 = {1, 2, 3, 4, 5};
    std::vector<int> list2 = {4, 5, 6, 7, 8, 5};

    std::unordered_set<int> matches = findUniqueMatches(list1, list2);
    
    std::cout << "Unique matches: ";
    for (int match : matches) {
        std::cout << match << " ";  // Output: 4 5
    }
    std::cout << std::endl;

    return 0;
}
