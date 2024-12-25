#include <stdio.h>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>

enum LogLevel {
    ERROR = 0,
    WARN,
    INFO,
    DEBUG
};

class Logger {
public:
    Logger() : logLevel(INFO), logEnabled(true) {}

    void setLogLevel(LogLevel level) {
        logLevel = level;
    }

    void setLogEnabled(bool enabled) {
        logEnabled = enabled;
    }

    void log(LogLevel level, const char* message) {
        if (logEnabled && level <= logLevel) {
            const char* levelStr = levelToString(level);
            printf("[%s] %s\n", levelStr, message);
        }
    }

private:
    LogLevel logLevel;
    std::atomic<bool> logEnabled;

    const char* levelToString(LogLevel level) {
        switch (level) {
            case ERROR: return "ERROR";
            case WARN: return "WARN";
            case INFO: return "INFO";
            case DEBUG: return "DEBUG";
            default: return "UNKNOWN";
        }
    }
};

void stressTest(Logger* logger) {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    const int numIterations = 1000000;

    for (int i = 0; i < numIterations; ++i) {
        logger->log(DEBUG, "Debug message in iteration %d", i);
    }

    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end - start;

    printf("Test with logging enabled: %.3f milliseconds\n", elapsed_time.count());
}

int main() {
    Logger logger;

    logger.setLogLevel(DEBUG);

    // Test with logging enabled
    stressTest(&logger);

    // Test with logging disabled (for performance comparison)
    logger.setLogEnabled(false);
    stressTest(&logger);

    return 0;
}
