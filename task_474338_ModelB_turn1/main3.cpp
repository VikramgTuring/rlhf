#include <fstream>

int main() {
    std::ofstream logfile("debug.log");
    if (logfile.is_open()) {
        std::cout.rdbuf(logfile.rdbuf());
        printf("Debug information logged in debug.log\n");
    } else {
        printf("Failed to open log file.\n");
    }
    return 0;
}
