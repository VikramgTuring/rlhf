#include <iostream>
#include <vector>
#include <unordered_set>

int countMatches(const std::vector<int>& list1, const std::vector<int>& list2) {
    // Step 1: Insert all elements from list2 into an unordered_set for fast lookups.
    std::unordered_set<int> setList2(list2.begin(), list2.end());

    // Step 2: Iterate over list1 and count how many elements exist in setList2.
    int count = 0;
    for (const int& item : list1) {
        if (setList2.find(item) != setList2.end()) {
            ++count;
        }
    }
    return count;
}

int main() {
    std::vector<int> list1 = {1, 2, 3, 4, 5};
    std::vector<int> list2 = {4, 5, 6, 7, 8, 1};

    int matches = countMatches(list1, list2);
    std::cout << "Count of matches: " << matches << std::endl;
    return 0;
}
