#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <chrono>
#include <cstring>

#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_ERROR 3

class Logger {
public:
    Logger(const std::string& filename, int logLevel = LOG_LEVEL_INFO)
        : log_level(logLevel), stop_logging(false) {
        log_file.open(filename, std::ios::out | std::ios::app);
        logging_thread = std::thread(&Logger::process_log_queue, this);
    }

    ~Logger() {
        stop_logging = true;
        cv.notify_all();
        logging_thread.join();
        if (log_file.is_open()) {
            log_file.close();
        }
    }

    void log(const std::string& message, int level = LOG_LEVEL_INFO) {
        if (level >= log_level) {  // Check if the message level is appropriate to log
            std::lock_guard<std::mutex> lock(mtx);
            log_queue.push(message);
            cv.notify_one();
        }
    }

private:
    void process_log_queue() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return !log_queue.empty() || stop_logging; });
            while (!log_queue.empty()) {
                // Use printf for direct console logging when needed
                std::cout << log_queue.front() << std::endl;
                log_file << log_queue.front() << std::endl;  // Log to file
                log_queue.pop();
            }
            if (stop_logging && log_queue.empty()) {
                break;
            }
        }
    }

    std::ofstream log_file;
    std::queue<std::string> log_queue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread logging_thread;
    int log_level; // Logging level
    bool stop_logging;
};

// Define states
enum class HardwareState {
    INITIALIZING,
    RUNNING,
    ERROR,
    SHUTDOWN
};

// Function to simulate state transition
void transitionState(HardwareState& currentState, HardwareState newState, Logger& logger) {
    static int transitions_logged = 0;

    // Log on significant state change or every nth transition
    if (currentState != newState || transitions_logged % 5 == 0) {
        logger.log("Transitioning from " + std::to_string(static_cast<int>(currentState)) +
                   " to " + std::to_string(static_cast<int>(newState)), LOG_LEVEL_INFO);
        currentState = newState;
    }
    transitions_logged++;
}

int main() {
    Logger logger("hardware_log.txt", LOG_LEVEL_INFO);

    HardwareState currentState = HardwareState::INITIALIZING;

    // Simulate state transitions
    transitionState(currentState, HardwareState::RUNNING, logger);
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Simulate time
    transitionState(currentState, HardwareState::ERROR, logger);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    transitionState(currentState, HardwareState::SHUTDOWN, logger);
    transitionState(currentState, HardwareState::SHUTDOWN, logger); // Repeated state won't log
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    transitionState(currentState, HardwareState::RUNNING, logger);

    return 0;
}
