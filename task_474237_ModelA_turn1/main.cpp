#include <iostream>
#include <chrono>
#include <vector>

class Base {
public:
    virtual void operation() {
        // Default operation
    }
    virtual ~Base() = default;
};

class DerivedA : public Base {
public:
    void operation() override {
        // Specific operation for DerivedA
        for (volatile int i = 0; i < 1000; ++i); // Simulating work
    }
};

class DerivedB : public Base {
public:
    void operation() override {
        // Specific operation for DerivedB
        for (volatile int i = 0; i < 1000; ++i); // Simulating work
    }
};

// Static Dispatch using templates
template <typename T>
void staticDispatchOperation() {
    T obj;
    obj.operation();
}

// Function to benchmark execution time
template <typename Func>
long long benchmark(Func func, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        func();
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    const int iterations = 10000;

    // Dynamic Dispatch
    std::vector<Base*> objects;
    objects.push_back(new DerivedA());
    objects.push_back(new DerivedB());

    auto dynamicDispatchTime = benchmark([&]() {
        for (auto obj : objects) {
            obj->operation();
        }
    }, iterations);

    // Static Dispatch
    auto staticDispatchTimeA = benchmark(staticDispatchOperation<DerivedA>, iterations);
    auto staticDispatchTimeB = benchmark(staticDispatchOperation<DerivedB>, iterations);

    // Output results
    std::cout << "Dynamic Dispatch Time: " << dynamicDispatchTime << " microseconds\n";
    std::cout << "Static Dispatch (DerivedA) Time: " << staticDispatchTimeA << " microseconds\n";
    std::cout << "Static Dispatch (DerivedB) Time: " << staticDispatchTimeB << " microseconds\n";

    // Cleanup
    for (auto obj : objects) {
        delete obj;
    }

    return 0;
}
