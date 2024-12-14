#include <iostream>
#include <chrono>
#include <memory>
#include <thread>
#include <cstdlib>
#include <sys/resource.h>

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

// Function to get current memory usage
long getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // Maximum resident set size used (in KB)
}

// Main function to test performance
int main() {
    // Measure memory usage before Singleton creation
    long memoryBefore = getMemoryUsage();
    std::cout << "Memory Before Singleton: " << memoryBefore << " KB" << std::endl;

    // Measure response time for Singleton access and method call
    auto start = std::chrono::high_resolution_clock::now();
    Singleton& instance = Singleton::getInstance();
    instance.doSomething(); // Call a method on the Singleton
    auto end = std::chrono::high_resolution_clock::now();

    // Measure memory usage after Singleton creation
    long memoryAfter = getMemoryUsage();
    std::cout << "Memory After Singleton: " << memoryAfter << " KB" << std::endl;

    // Calculate response time
    std::chrono::duration<double, std::milli> responseTime = end - start;
    std::cout << "Response Time: " << responseTime.count() << " ms" << std::endl;

    return 0;
}
