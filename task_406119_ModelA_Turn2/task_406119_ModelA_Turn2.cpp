#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

int main() {
    const int size = 1000000;
    std::vector<int> arr(size);

    // Generate a large unsorted array
    for (int i = 0; i < size; ++i) {
        arr[i] = std::rand() % 10000;
    }

    const int target = 3789; // Arbitrary target to search for

    // Performance measurement without custom comparator (sequential search)
    std::clock_t start = std::clock();
    auto it = std::find(arr.begin(), arr.end(), target);
    std::clock_t end = std::clock();
    double time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    if (it != arr.end()) {
        std::cout << "Found " << target << " at index " << std::distance(arr.begin(), it) << std::endl;
    }
    else {
        std::cout << target << " not found" << std::endl;
    }

    std::cout << "Time taken without custom comparator: " << time_taken << " seconds" << std::endl;

    // Sort the array using default comparison (ascending order)
    std::sort(arr.begin(), arr.end());

    // Performance measurement with custom comparator for binary search
    start = std::clock();
    auto it2 = std::lower_bound(arr.begin(), arr.end(), target);
    end = std::clock();
    time_taken = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    if (it2 != arr.end() && *it2 == target) {
        std::cout << "Found " << target << " at index " << std::distance(arr.begin(), it2) << std::endl;
    }
    else {
        std::cout << target << " not found" << std::endl;
    }

    std::cout << "Time taken with custom comparator: " << time_taken << " seconds" << std::endl;

    return 0;
}