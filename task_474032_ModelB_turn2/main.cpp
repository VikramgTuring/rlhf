#include <iostream>
#include <chrono>
#include <cstdlib>
#include <array>
#include <map>
#include <functional>
#include <vector>

const int NUM_ITERATIONS = 10000000;

using CondResultFn = std::function<int(int)>;

// Check with or without inline declarations in switch to compare performance impact.

// Switch statement implementation
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

// 1. Lookup Table (LUT) Approach
int decisionMakingLUT(int value) {
    static const int lut[11] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 0};
    return value < 11 ? lut[value] : 0;
}

// 2. Array of Function Pointers/Lambdas
int decisionMakingArray(int value) {
    static const CondResultFn funcs[] = {
        [](int v) { if (v == 1) return 10; return 0; },
        [](int v) { if (v == 2) return 20; return 0; },
        [](int v) { if (v == 3) return 30; return 0; },
        [](int v) { if (v == 4) return 40; return 0; },
        [](int v) { if (v == 5) return 50; return 0; },
        [](int v) { if (v == 6) return 60; return 0; },
        [](int v) { if (v == 7) return 70; return 0; },
        [](int v) { if (v == 8) return 80; return 0; },
        [](int v) { if (v == 9) return 90; return 0; },
        // Add a default
        [](int) { return 0; }
    };

    if (value < sizeof(funcs) / sizeof(funcs[0]))
        return funcs[value](value);
    return 0;
}

// 3. Map of Function Pointers
int decisionMakingMap(int value) {
    static const std::map<int, CondResultFn> funcs = {
        {1, [](int) { return 10; } },
        {2, [](int) { return 20; } },
        {3, [](int) { return 30; } },
        {4, [](int) { return 40; } },
        {5, [](int) { return 50; } },
        {6, [](int) { return 60; } },
        {7, [](int) { return 70; } },
        {8, [](int) { return 80; } },
        {9, [](int) { return 90; } },
    };

    auto it = funcs.find(value);
    if (it != funcs.end())
        return it->second(value);
    return 0;
}

// 4. Polymorphism (Simple Class Example)
class DecisionMaker {
public:
    virtual int makeDecision(int value) = 0;
};

class DecisionMaker1 : public DecisionMaker {
public:
    int makeDecision(int value) override {
        return value == 1 ? 10 : 0;
    }
};

// And so on for DecisionMaker2...DecisionMaker9

class DecisionMakerDefault : public DecisionMaker {
public:
    int makeDecision(int value) override {
        return 0;
    }
};

std::vector<DecisionMaker*> makers = { new DecisionMaker1(), new DecisionMaker2(), /* add all */ , new DecisionMakerDefault() };

int decisionMakingPolymorphic(int value) {
    if (value >= 0 && value < makers.size())
        return makers[value]->makeDecision(value);
    return 0;
}

void measurePerformance() {
    int randomValue;

    // Measure performance of switch
    auto startSwitch = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        randomValue = rand() % 11; // Random values between 0 and 10
        decisionMakingSwitch(randomValue);
    }
    auto endSwitch = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSwitch = endSwitch - startSwitch;

    // Measure performance of other methods
    // Similar code for LUT, Array, Map, and Polymorphism will follow

    std::cout << "Switch Duration: " << durationSwitch.count() << " seconds\n";
    // std::cout << "LUT Duration: " << durationLUT.count() << " seconds\n";
    // And so on...
}

int main() {
    measurePerformance();

    // Remember to delete pointers used in the polymorphic approach to avoid memory leaks.
    // for (auto maker : makers)
    //    delete maker;

    return 0;
}
