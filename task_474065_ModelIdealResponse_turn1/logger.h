#include <iostream>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <condition_variable>

class Logger {
public:
    Logger(const std::string& filename) : stop_logging(false) {
        log_file.open(filename, std::ios::out | std::ios::app);
        logging_thread = std::thread(&Logger::process_log_queue, this);
    }

    ~Logger() {
        stop_logging = true;
        cv.notify_all();  // Wake up the logging thread
        logging_thread.join();
        if (log_file.is_open()) {
            log_file.close();
        }
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        log_queue.push(message);
        cv.notify_one(); // Notify the logging thread to process the queue
    }

private:
    void process_log_queue() {
        while (!stop_logging) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return !log_queue.empty() || stop_logging; });
            while (!log_queue.empty()) {
                log_file << log_queue.front() << std::endl;
                log_queue.pop();
            }
        }
    }

    std::ofstream log_file;
    std::queue<std::string> log_queue;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread logging_thread;
    bool stop_logging;
};
