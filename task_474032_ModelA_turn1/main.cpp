#include <iostream>
#include <chrono>
#include <cstdlib>

const int NUM_ITERATIONS = 10000000;

// Using if-else statements
int decisionMakingIfElse(int value) {
    if (value == 1) return 10;
    else if (value == 2) return 20;
    else if (value == 3) return 30;
    else if (value == 4) return 40;
    else if (value == 5) return 50;
    else if (value == 6) return 60;
    else if (value == 7) return 70;
    else if (value == 8) return 80;
    else if (value == 9) return 90;
    else return 0; // Default case
}

// Using switch statement
int decisionMakingSwitch(int value) {
    switch (value) {
        case 1: return 10;
        case 2: return 20;
        case 3: return 30;
        case 4: return 40;
        case 5: return 50;
        case 6: return 60;
        case 7: return 70;
        case 8: return 80;
        case 9: return 90;
        default: return 0; // Default case
    }
}

void measurePerformance() {
    int randomValue;

    // Measure performance of if-else
    auto startIfElse = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        randomValue = rand() % 11; // Random values between 0 and 10
        decisionMakingIfElse(randomValue);
    }
    auto endIfElse = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationIfElse = endIfElse - startIfElse;
    std::cout << "If-Else Duration: " << durationIfElse.count() << " seconds\n";

    // Measure performance of switch
    auto startSwitch = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        randomValue = rand() % 11; // Random values between 0 and 10
        decisionMakingSwitch(randomValue);
    }
    auto endSwitch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSwitch = endSwitch - startSwitch;
    std::cout << "Switch Duration: " << durationSwitch.count() << " seconds\n";
}

int main() {
    measurePerformance();
    return 0;
}
