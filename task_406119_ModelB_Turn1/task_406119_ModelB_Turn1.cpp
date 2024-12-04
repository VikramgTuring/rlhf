#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// Custom comparison function for sorting integers in descending order
bool customCompareDesc(int a, int b) {
    return a > b;
}

// Custom comparison function for searching for a key in a vector sorted in descending order
bool customCompareDescFind(int key, int val) {
    return key > val;
}

int main() {
    const int size = 1000000;

    // Generate a large random vector
    std::vector<int> data(size);
    for (int& i : data) {
        i = rand() % 1000000;
    }

    // Scenario 1: Sorting without custom comparator (default ascending order)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(data.begin(), data.end());
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;
        std::cout << "Sorting time without custom comparator (ascending): " << elapsed_time.count() << " seconds\n";
    }

    // Scenario 2: Sorting with custom comparator (descending order)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(data.begin(), data.end(), customCompareDesc);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;
        std::cout << "Sorting time with custom comparator (descending): " << elapsed_time.count() << " seconds\n";
    }

    // Scenario 3: Binary search without custom comparator (assuming data is sorted in ascending order)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int target = data[size / 2];
        auto it = std::binary_search(data.begin(), data.end(), target);
        bool found = it != data.end();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;
        std::cout << "Binary search time without custom comparator: " << elapsed_time.count() << " seconds\n";
        if (found) {
            std::cout << "Element found at index: " << std::distance(data.begin(), it) << std::endl;
        }
        else {
            std::cout << "Element not found" << std::endl;
        }
    }

    // Scenario 4: Binary search with custom comparator (data is sorted in descending order)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int target = data[size / 2];
        auto it = std::binary_search(data.begin(), data.end(), target, customCompareDescFind);
        bool found = it != data.end();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;
        std::cout << "Binary search time with custom comparator: " << elapsed_time.count() << " seconds\n";
        if (found) {
            std::cout << "Element found at index: " << std::distance(data.begin(), it) << std::endl;
        }
        else {
            std::cout << "Element not found" << std::endl;
        }
    }

    return 0;
}

