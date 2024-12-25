#include <stdarg.h>  // For va_list
#include <stdio.h>    // For printf
#include <iostream>

enum LogLevel {
    LOG_ERROR = 0,   // Lowest verbosity, critical errors
    LOG_WARNING,     // Non-critical issues
    LOG_INFO,        // General information
    LOG_DEBUG,        // Debugging details
    LOG_VERBOSE       // Highest verbosity, trace information
};

LogLevel globalLogLevel = LOG_DEBUG; // Adjust this as needed

void logMessage(LogLevel level, const char* format, ...) {
    if (level >= globalLogLevel) {
        fputs("[", stdout);
        switch (level) {
            case LOG_ERROR: fputs("ERROR", stdout); break;
            case LOG_WARNING: fputs("WARNING", stdout); break;
            case LOG_INFO: fputs("INFO", stdout); break;
            case LOG_DEBUG: fputs("DEBUG", stdout); break;
            case LOG_VERBOSE: fputs("VERBOSE", stdout); break;
        }
        fputs("] ", stdout);

        va_list args;
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
        fputs("\n", stdout);
    }
}
int main() {
    logMessage(LOG_INFO, "Application started.");
    logMessage(LOG_DEBUG, "Processing data array of size %zu", 1024);
    //  (More code)
    logMessage(LOG_WARNING, "Memory usage is high: %.2lf%%", 85.7);
    logMessage(LOG_ERROR, "Fatal error occurred: %s", "Segmentation fault");
    return 0;
}

