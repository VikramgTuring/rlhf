#include <iostream>
#include <chrono>
#include <random>

// Function to perform decision making using if-else
int decisionMakingIfElse(int choice) {
    if (choice == 1) {
        return 10;
    } else if (choice == 2) {
        return 20;
    } else if (choice == 3) {
        return 30;
    } else {
        return 0;
    }
}

// Function to perform decision making using switch
int decisionMakingSwitch(int choice) {
    switch (choice) {
        case 1:
            return 10;
        case 2:
            return 20;
        case 3:
            return 30;
        default:
            return 0;
    }
}

int main() {
    const int numIterations = 1000000;
    int randomChoice;

    // Performance measurement using if-else
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numIterations; ++i) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 4);
            randomChoice = dis(gen);
            decisionMakingIfElse(randomChoice);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken using if-else: " << duration.count() << " seconds" << std::endl;
    }

    // Performance measurement using switch
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < numIterations; ++i) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 4);
            randomChoice = dis(gen);  
            decisionMakingSwitch(randomChoice);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken using switch: " << duration.count() << " seconds" << std::endl;
    }

    return 0;
}
