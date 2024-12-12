#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <chrono>

std::mutex m1;
std::mutex m2;

int shared_counter = 0;

const int NUM_THREADS = 100;
const int NUM_ITERATIONS = 100000;

void increment_counter(bool use_scoped_lock) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        if (use_scoped_lock) {
            std::scoped_lock lock({m1, m2});
            shared_counter++;
        } else {
            std::lock_guard<std::mutex> lock1(m1);
            std::lock_guard<std::mutex> lock2(m2);
            shared_counter++;
        }
    }
}

void test_scoped_lock() {
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.push_back(std::thread(increment_counter, true));  // Use scoped_lock
    }

    for (std::thread& thread : threads) {
        thread.join();
    }
}

void test_manual_locking() {
    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.push_back(std::thread(increment_counter, false)); // Manual locking
    }

    for (std::thread& thread : threads) {
        thread.join();
    }
}

int main() {
    std::cout << "Testing with std::scoped_lock:\n";
    test_scoped_lock();
    std::cout << "Final shared_counter value: " << shared_counter << std::endl;

    shared_counter = 0; // Reset counter for the next test

    std::cout << "\nTesting with manual locking:\n";
    test_manual_locking();
    std::cout << "Final shared_counter value: " << shared_counter << std::endl;

    return 0;
}
