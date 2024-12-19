#include <spdlog/spdlog.h>

void custom_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    const std::string str = vfprintf(nullptr, format, args);
    va_end(args);
    spdlog::info(str);
}
void performComputation(int id) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Change printf to custom_printf
        custom_printf("Thread %d: Iteration %d\n", id, i);
    }
}
void performComputation(int id) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        spdlog::info("Thread {}: Iteration {}", id, i);
    }
}
int main() {
    // Set up logging to the console
    auto console = spdlog::stdout_color_mt("console");

    // You can add more sinks for different destinations
    // Example: auto file = spdlog::basic_logger_mt("file", "logs/application.log");

    // Configure the log level (debug, info, warning, error, etc.)
    console->set_level(spdlog::level::info);

    std::thread t1(performComputation, 1);
    std::thread t2(performComputation, 2);

    t1.join();
    t2.join();

    return 0;
}
