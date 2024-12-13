#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

const int NUM_THREADS = 100;
const int NUM_ITERATIONS = 1000000;

std::mutex m1, m2;
std::atomic<int> counter1 = 0;
std::atomic<int> counter2 = 0;

void incrementCounter1(int id) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::scoped_lock lock(m1);
        counter1++;
    }
}

void incrementCounter2(int id) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::scoped_lock lock(m2);
        counter2++;
    }
}

void incrementCounterBoth1(int id) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::lock_guard<std::mutex> lock1(m1);
        std::lock_guard<std::mutex> lock2(m2);
        counter1++;
        counter2++;
    }
}

void incrementCounterBoth2(int id) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::lock(m1, m2);
        counter1++;
        counter2++;
    }
}

void incrementCounterBoth3(int id) {
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        std::scoped_lock<std::mutex, std::mutex> lock(m1, m2);
        counter1++;
        counter2++;
    }
}

int main() {
    std::thread threads[NUM_THREADS];

    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_THREADS / 2; ++i) {
            threads[i] = std::thread(incrementCounter1, i);
        }

        for (int i = NUM_THREADS / 2; i < NUM_THREADS; ++i) {
            threads[i] = std::thread(incrementCounter2, i);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Incrementing counters separately: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_THREADS; ++i) {
            threads[i] = std::thread(incrementCounterBoth1, i);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Incrementing counters both (manual lock): "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_THREADS; ++i) {
            threads[i] = std::thread(incrementCounterBoth2, i);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Incrementing counters both (std::lock): "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < NUM_THREADS; ++i) {
            threads[i] = std::thread(incrementCounterBoth3, i);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Incrementing counters both (std::scoped_lock): "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us" << std::endl;
    }

    std::cout << "Final values: counter1 = " << counter1 << ", counter2 = " << counter2 << std::endl;

    return 0;
}
