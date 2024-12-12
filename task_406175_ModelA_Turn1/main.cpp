#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::mutex mutex1;
std::mutex mutex2;

// Using std::scoped_lock
void function_with_scoped_lock() {
    std::scoped_lock<std::mutex&, std::mutex&> lock(mutex1, mutex2);
    // Critical section
}

// Manually locking multiple mutexes
void function_with_manual_lock() {
    std::lock_guard<std::mutex> lock1(mutex1);
    std::lock_guard<std::mutex> lock2(mutex2);
    // Critical section
}

int main() {
    const int num_threads = 100;
    const int iterations = 100000;
    std::vector<std::thread> threads;

    {
        // Measure time for function_with_scoped_lock
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&] {
                for (int j = 0; j < iterations; ++j) {
                    function_with_scoped_lock();
                }
            });
        }
        for (std::thread& thread : threads) {
            thread.join();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Time taken with std::scoped_lock: " << duration.count() << " microseconds\n";
    }

    {
        // Measure time for function_with_manual_lock
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&] {
                for (int j = 0; j < iterations; ++j) {
                    function_with_manual_lock();
                }
            });
        }
        for (std::thread& thread : threads) {
            thread.join();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Time taken with manual locking: " << duration.count() << " microseconds\n";
    }

    return 0;
}
