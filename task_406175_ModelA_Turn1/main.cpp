#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <vector>

#define NUM_THREADS 10
#define NUM_ITERATIONS 1000000

std::mutex mtx1;
std::mutex mtx2;
std::atomic<int> shared_counter1{0};
std::atomic<int> shared_counter2{0};

void increment_counters_with_std_scoped_lock() {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::scoped_lock<std::mutex, std::mutex> lock(mtx1, mtx2);
        shared_counter1++;
        shared_counter2++;
    }
}

void increment_counters_manually() {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::lock_guard<std::mutex> lock1(mtx1);
        std::lock_guard<std::mutex> lock2(mtx2);
        shared_counter1++;
        shared_counter2++;
    }
}

int main() {
    {
        std::cout << "\nRunning with std::scoped_lock...\n";
        std::vector<std::thread> threads;
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_THREADS; ++i) {
            threads.emplace_back(increment_counters_with_std_scoped_lock);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken with std::scoped_lock: " << duration.count() << " microseconds\n";
        std::cout << "Final value of shared_counter1: " << shared_counter1.load() << std::endl;
        std::cout << "Final value of shared_counter2: " << shared_counter2.load() << std::endl;
    }

    {
        shared_counter1 = 0;
        shared_counter2 = 0;

        std::cout << "\nRunning with manual locking...\n";
        std::vector<std::thread> threads;
        auto start = std::chrono::high_resolution_clock::now(); 
        for (int i = 0; i < NUM_THREADS; ++i) {
            threads.emplace_back(increment_counters_manually);
        }

        for (auto& thread : threads) {
            thread.join();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Time taken with manual locking: " << duration.count() << " microseconds\n";
        std::cout << "Final value of shared_counter1: " << shared_counter1.load() << std::endl;
        std::cout << "Final value of shared_counter2: " << shared_counter2.load() << std::endl;
    }
    return 0;
}  

