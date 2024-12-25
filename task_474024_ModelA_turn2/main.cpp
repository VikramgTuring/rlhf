#include <iostream>
#include <fstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <string>
#include <functional>

enum LogLevel {
    ERROR = 0,
    WARN,
    INFO,
    DEBUG
};

class Logger {
public:
    Logger() : logLevel(INFO), isRunning(true) {
        logThread = std::thread(&Logger::processLogs, this);
    }

    ~Logger() {
        isRunning = false;
        cv.notify_all();
        if (logThread.joinable()) {
            logThread.join();
        }
    }

    void setLogLevel(LogLevel level) {
        logLevel = level;
    }

    // Only creates the message string if the level is enabled
    template<typename... Args>
    void log(LogLevel level, const char* format, Args... args) {
        if (level <= logLevel) {
            // Create log message string and enqueue it
            char buffer[256];
            snprintf(buffer, sizeof(buffer), format, args...);
            {
                std::lock_guard<std::mutex> lock(mtx);
                logQueue.push(std::string(buffer));
            }
            cv.notify_one(); // Notify the log processing thread
        }
    }

private:
    LogLevel logLevel;
    std::queue<std::string> logQueue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread logThread;
    std::atomic<bool> isRunning;

    void processLogs() {
        while (isRunning) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return !logQueue.empty() || !isRunning; });
            
            while (!logQueue.empty()) {
                std::string logMessage = std::move(logQueue.front());
                logQueue.pop();
                lock.unlock(); // Unlock before I/O operation
                std::cout << logMessage << std::endl; // Output can be changed to file or other sinks
                lock.lock(); // Lock again before checking the queue
            }
        }
    }
};

int main() {
    Logger logger;
    logger.setLogLevel(DEBUG); // Set log level to DEBUG for verbosity

    logger.log(ERROR, "This is an error message: %d", -1);
    logger.log(WARN, "This is a warning message: %s", "Warning!");
    logger.log(INFO, "This is an info message.");
    logger.log(DEBUG, "This is a debug message with a number: %d", 42);

    // You could simulate more logging here...

    return 0;
}
