#include <iostream>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>

class Logger {
public:
    enum LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    Logger() = default;

    void log(LogLevel level, const std::string& message) {
        std::string prefix = getTimestamp() + " [" + logLevelToString(level) + "] ";
        printf("%s%s\n", prefix.c_str(), message.c_str());
    }

private:
    std::string getTimestamp() {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&now_time_t);
        
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now_tm);
        return buffer;
    }

    std::string logLevelToString(LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
};

class PredictiveAlgorithm {
public:
    PredictiveAlgorithm(): logger() {}

    void runAlgorithm(int input) {
        logger.log(Logger::INFO, "Running algorithm with input: " + std::to_string(input));

        if (input < 0) {
            logger.log(Logger::ERROR, "Input cannot be negative. Received: " + std::to_string(input));
            return; // Exit if the input is invalid
        }

        logger.log(Logger::INFO, "Assumption - Input is non-negative.");
        
        int result = performCalculation(input);
        
        logger.log(Logger::INFO, "Calculation result for input " + std::to_string(input) + " is: " + std::to_string(result));
        
        if (result > 100) {
            logger.log(Logger::WARNING, "Result is unusually high: " + std::to_string(result));
        }
    }

private:
    Logger logger;

    int performCalculation(int input) {
        logger.log(Logger::DEBUG, "Performing calculation with input: " + std::to_string(input));
        return input * 2; // Simple calculation
    }
};

int main() {
    PredictiveAlgorithm algorithm;
    
    algorithm.runAlgorithm(50);
    algorithm.runAlgorithm(-10);
    algorithm.runAlgorithm(75);
    
    return 0;
}
