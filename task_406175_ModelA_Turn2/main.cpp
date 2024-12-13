#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

#define NUM_THREADS 10
#define NUM_ITERATIONS 1000

std::mutex smaller_mtx;
std::mutex larger_mtx;

int main() {
    {
        std::cout << "\nRunning with hierarchical manual locking...\n";
        std::vector<std::thread> threads;

        for (int i = 0; i < NUM_THREADS; ++i) {
            threads.emplace_back([&]{
                for (int i = 0; i < NUM_ITERATIONS; ++i) {
                    {
                        std::lock_guard<std::mutex> lock(smaller_mtx);
                        // Do something with smaller critical section
                    }
                    {
                        std::lock_guard<std::mutex> lock1(smaller_mtx);
                        std::lock_guard<std::mutex> lock2(larger_mtx);
                        // Do something with both critical sections, larger after smaller to ensure hierarchy
                    }
                }
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
    return 0;
}

