#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

class Profiler {
public:
    Profiler(const std::string& name) : name(name) {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Profiler() {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Execution time for " << name << ": " << elapsed.count() << " seconds\n";
    }

private:
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
