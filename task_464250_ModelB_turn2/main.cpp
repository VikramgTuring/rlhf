#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>

enum LogLevel {
    LOG_INFO = 0,
    LOG_ERROR = 1,
    LOG_WARNING = 2,
    LOG_DEBUG = 3,
};

const char* logLevelStrings[] = {
    "INFO",
    "ERROR",
    "WARNING",
    "DEBUG"
};

void logMessage(LogLevel level, const char* message, const char* file = __FILE__, int line = __LINE__) {
    time_t now = time(0);
    struct tm* tstruct = localtime(&now);
    char timestr[80];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tstruct);

    fprintf(stderr, "%s [%s][%s:%d]: %s\n",
            timestr, logLevelStrings[level],
            file, line, message);
}

class PredictiveAlgorithm {
public:
    void runAlgorithm(int input) {
        logMessage(LOG_INFO, "Running algorithm with input: %d", input);

        if (input < 0) {
            logMessage(LOG_ERROR, "Input cannot be negative. Received: %d", input);
            return;
        }

        logMessage(LOG_INFO, "Assumption - Input is non-negative.");

        int result = performCalculation(input);

        logMessage(LOG_INFO, "Calculation result for input %d is: %d", input, result);

        if (result > 100) {
            logMessage(LOG_WARNING, "Result is unusually high: %d", result);
        }
    }

private:
    int performCalculation(int input) {
        logMessage(LOG_DEBUG, "Performing calculation with input: %d", input);
        return input * 2;
    }
};

int main() {
    PredictiveAlgorithm algorithm;
    algorithm.runAlgorithm(50);
    algorithm.runAlgorithm(-10);
    algorithm.runAlgorithm(75);

    return 0;
}
