#include <stdio.h>
#include <sys/time.h>

void printTimestampedMessage(const char *message) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    char timestamp[26];
    snprintf(timestamp, sizeof(timestamp), "%02d:%02d:%02d.%06d",
            tv.tv_sec / 3600, (tv.tv_sec % 3600) / 60, tv.tv_sec % 60, tv.tv_usec);

    printf("[%s] %s\n", timestamp, message);
}

int main() {
    printTimestampedMessage("Starting hardware interaction.");

    // Hardware interaction code here

    printTimestampedMessage("Hardware interaction completed.");

    return 0;
}
