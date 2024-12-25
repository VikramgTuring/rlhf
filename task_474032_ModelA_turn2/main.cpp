#include <iostream>
#include <chrono>
#include <map>
#include <cstdlib>

const int NUM_ITERATIONS = 1000;

// Using a lookup table for decision making
std::map<int, int> lookupTable = {
    {1, 10},
    {2, 20},
    {3, 30},
    {4, 40},
    {5, 50},
    {6, 60},
    {7, 70},
    {8, 80},
    {9, 90}
};

int decisionMakingLookup(int value) {
    // Using .count() to check if key exists
    if (lookupTable.count(value)) {
        return lookupTable[value];
    }
    return 0; // Default case
}

// Measure performance of different decision-making approaches
void measurePerformance() {
    int randomValue;

    // Measure performance of lookup table
    auto startLookup = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        randomValue = rand() % 11; // Random values between 0 and 10
        decisionMakingLookup(randomValue);
    }
    auto endLookup = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationLookup = endLookup - startLookup;
    std::cout << "Lookup Table Duration: " << durationLookup.count() << " seconds\n";

    // Measure performance of if-else
    auto startIfElse = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        randomValue = rand() % 11; // Random values between 0 and 10
        if (randomValue == 1) std::cout << 10;
        else if (randomValue == 2) std::cout << 20;
        else if (randomValue == 3) std::cout << 30;
        else if (randomValue == 4) std::cout << 40;
        else if (randomValue == 5) std::cout << 50;
        else if (randomValue == 6) std::cout << 60;
        else if (randomValue == 7) std::cout << 70;
        else if (randomValue == 8) std::cout << 80;
        else if (randomValue == 9) std::cout << 90;
        else std::cout << 0; // Default case
    }
    auto endIfElse = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationIfElse = endIfElse - startIfElse;
    std::cout << "If-Else Duration: " << durationIfElse.count() << " seconds\n";
}

int main() {
    measurePerformance();
    return 0;
}
