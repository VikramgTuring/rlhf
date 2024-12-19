#include <spdlog/spdlog.h>
#include <thread>
#include <chrono>

void performComputation(int id) {
    for (int i = 0; i < 10; ++i) {
        // Simulate computation
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        spdlog::info("Thread {}: Iteration {}", id, i);
    }
}

int main() {
    // Set up logging
    spdlog::set_pattern("%Y-%m-%d %H:%M:%S [%l] %v"); // Timestamp and log level
    spdlog::set_level(spdlog::level::info); // Set log level

    std::thread t1(performComputation, 1);
    std::thread t2(performComputation, 2);

    t1.join();
    t2.join();

    return 0;
}
