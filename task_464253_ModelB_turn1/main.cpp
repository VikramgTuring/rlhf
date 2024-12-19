#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

// Log using printf
void log_with_printf(const char* format, ...) {
    va_list arg;
    va_start(arg, format);
    vprintf(format, arg);
    va_end(arg);
}

// Custom logger using ostream
class CustomLogger {
public:
    explicit CustomLogger(const string& filename) : logfile(filename.c_str()) {}

    void log(const string& message) {
        lock_guard<mutex> lock(mtx);
        logfile << message << endl;
    }

private:
    ofstream logfile;
    mutex mtx;
};

int main() {
    const int NUM_THREADS = 10;
    const int LOG_COUNT = 100000;

    // Using printf for logging
    log_with_printf("Application started with %d threads\n", NUM_THREADS);

    vector<thread> threads;

    // Custom logger instance
    CustomLogger customLogger("application.log");

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back([i, &customLogger, LOG_COUNT] {
            for (int j = 0; j < LOG_COUNT; ++j) {
                // Logging using printf - Could cause contention in high-performance scenarios
                char log_str[128];
                snprintf(log_str, sizeof(log_str), "Thread %d: Iteration %d\n", i, j);
                log_with_printf(log_str);

                // Alternatively, using CustomLogger
                // customLogger.log(fmt::format("Thread {}: Iteration {}", i, j));
            }
        });
    }

    for (thread& t : threads) {
        t.join();
    }

    log_with_printf("Application completed\n");

    return 0;
}
