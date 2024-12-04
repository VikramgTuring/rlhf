
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>   // For std::clock
#include <ctime>    // For std::asctime
#include <random>

// Simple comparison function
bool compare_integers(int lhs, int rhs) {
    return lhs < rhs;
}

/* Custom comparator that sorts elements in descending order
This can be useful when your data is naturally in descending order
and you want to avoid the overhead of reversing the array manually. */
struct custom_compare {
    bool operator()(int lhs, int rhs) const {
        return lhs > rhs;
    }
};

int main() {
    std::srand(static_cast<unsigned>(std::time(0)));

    size_t num_elements = 100000;
    std::vector<int> unsorted_array(num_elements);

    // Generate a large random unsorted array
    for (size_t i = 0; i < num_elements; ++i) {
        unsorted_array[i] = std::rand() % 1000000;
    }

    // Clone the original array for custom comparator usage
    std::vector<int> descending_array(unsorted_array);


    /* Scenario 1: Using default comparison function (sorting in ascending order) */
    std::clock_t start_time1 = std::clock();
    std::sort(unsorted_array.begin(), unsorted_array.end());
    std::clock_t end_time1 = std::clock();

    double time_elapsed1 = static_cast<double>(end_time1 - start_time1) / CLOCKS_PER_SEC;
    std::cout << "Time taken with default comparison function: " << time_elapsed1 << " seconds" << std::endl;


    /* Scenario 2: Using custom comparison function to sort in descending order */
    std::clock_t start_time2 = std::clock();
    std::sort(descending_array.begin(), descending_array.end(), custom_compare());
    std::clock_t end_time2 = std::clock();

    double time_elapsed2 = static_cast<double>(end_time2 - start_time2) / CLOCKS_PER_SEC;
    std::cout << "Time taken with custom comparison function: " << time_elapsed2 << " seconds" << std::endl;

    return 0;
}
