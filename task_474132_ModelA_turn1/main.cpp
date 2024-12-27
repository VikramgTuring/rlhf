#include <stdio.h>
#include <string>

enum LogLevel {
    ERROR = 0,
    WARN,
    INFO,
    DEBUG
};

class Logger {
public:
    Logger() : logLevel(INFO) {} // Default log level

    void setLogLevel(LogLevel level) {
        logLevel = level;
    }

    void log(LogLevel level, const char* message) {
        if (level <= logLevel) {
            const char* levelStr = levelToString(level);
            printf("[%s] %s\n", levelStr, message);
        }
    }

private:
    LogLevel logLevel;

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

int main() {
    Logger logger;

    // Set the log level to DEBUG for detailed logs during development
    logger.setLogLevel(DEBUG);

    logger.log(ERROR, "This is an error message.");
    logger.log(WARN, "This is a warning message.");
    logger.log(INFO, "This is an info message.");
    logger.log(DEBUG, "This is a debug message.");

    // Change log level to WARN
    logger.setLogLevel(WARN);
    logger.log(ERROR, "This is another error message.");
    logger.log(INFO, "This info message will not be displayed.");
    logger.log(DEBUG, "This debug message will not be displayed.");

    return 0;
}
