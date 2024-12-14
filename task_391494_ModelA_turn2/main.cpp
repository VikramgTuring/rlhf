#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <gperftools/profiler.h>

// Singleton class
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    void doSomething() {
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulated workload
    }

private:
    Singleton() {
        std::cout << "Singleton created." << std::endl;
    }

    ~Singleton() {
        std::cout << "Singleton destroyed." << std::endl;
    }

    Singleton(const Singleton&) = delete; // Prevent copy
    Singleton& operator=(const Singleton&) = delete; // Prevent assignment
};

// Main function to test performance
int main() {
    ProfilerStart("singleton_profile.prof"); // Start CPU profiling

    // Simulate multiple accesses to the Singleton
    for (int i = 0; i < 100; ++i) {
        Singleton::getInstance().doSomething();
    }

    ProfilerStop(); // Stop CPU profiling

    return 0;
}
