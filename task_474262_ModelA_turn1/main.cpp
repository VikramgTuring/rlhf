#include <iostream>
#include <vector>
#include <set>

int countMatches(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Step 1: Insert all elements of list2 into a set for fast lookup
    std::set<int> setList2(list2.begin(), list2.end());
    
    // Step 2: Iterate over list1 and count how many elements exist in setList2
    int count = 0;
    for (const int& item : list1) {
        if (setList2.find(item) != setList2.end()) {
            ++count;  // Increment the count if item is found in set
        }
    }
    return count;  // Return the total count of matches
}

int main() {
    std::vector<int> list1 = {1, 2, 3, 4, 5};
    std::vector<int> list2 = {4, 5, 6, 7, 8};

    int matches = countMatches(list1, list2);
    std::cout << "Count of matches: " << matches << std::endl;  // Output: 2
    return 0;
}
