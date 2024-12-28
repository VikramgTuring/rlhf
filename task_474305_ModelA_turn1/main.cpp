#include <stdio.h>
#include <time.h>

void log_with_timestamp(const char *message) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    printf("[%ld.%09ld] %s\n", ts.tv_sec, ts.tv_nsec, message);
}

void hardware_interaction() {
    log_with_timestamp("Starting hardware interaction.");
    
    // Simulating hardware delay
    struct timespec req = {0, 500000000}; // 500 milliseconds
    nanosleep(&req, NULL);
    
    log_with_timestamp("Finished hardware interaction.");
}

int main() {
    log_with_timestamp("Program started.");
    hardware_interaction();
    log_with_timestamp("Program ended.");
    return 0;
}
