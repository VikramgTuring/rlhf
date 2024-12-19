#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h> // optional for colorful output
#include <thread>
#include <chrono>

void compute(int thread_id) {
    for (int i = 0; i < 5; ++i) {
        // Simulate computation work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Replaced printf with spdlog info
        spdlog::info("Thread {}: Computing iteration {}", thread_id, i);
        
        if (i == 2) {
            spdlog::info("Thread {}: Halfway there!", thread_id);
        }
    }
    
    // Use spdlog to indicate work is complete
    spdlog::info("Thread {}: Finished computation.", thread_id);
}

int main() {
    // Initializen and set format for spdlog
    spdlog::set_pattern("%Y-%m-%d %H:%M:%S [%^%l%$] %v"); // Set pattern for logs
    spdlog::set_level(spdlog::level::info); // Set global log level

    // Start threads for computation
    std::thread t1(compute, 1);
    std::thread t2(compute, 2);

    t1.join(); // Wait for threads to finish
    t2.join();

    return 0;
}
