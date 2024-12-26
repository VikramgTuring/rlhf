#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <queue>

// Global variable to disable printing
bool g_EnablePrinting = true;

// Function to safely print message
void SafePrint(const char* format, ...) {
    static std::queue<std::string> printQueue;

    // Acquire mutex to protect the print queue
    std::lock_guard<std::mutex> lock(printMutex);

    if (g_EnablePrinting) {
        va_list args;
        va_start(args, format);
        char buffer[256];
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        std::string printString(buffer);
        printQueue.push(printString);
    }
}

// Function to asynchronously write to file
void PrintToFileAsync() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(printMutex);

            while (!printQueue.empty()) {
                const std::string& printString = printQueue.front();
                logFile << printString << std::endl;
                logFile.flush();
                printQueue.pop();
            }
        }

        // Sleep for a short time before checking the queue again
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

// Implement hardware state machine example
enum class HardwareState {
    IDLE,
    WORKING,
    ERROR,
};

void SimulateHardwareStateMachine() {
    HardwareState currentState = HardwareState::IDLE;

    while (true) {
        switch (currentState) {
            case HardwareState::IDLE:
                SafePrint("Hardware State: IDLE\n");
                currentState = HardwareState::WORKING;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            case HardwareState::WORKING:
                SafePrint("Hardware State: WORKING\n");
                if (rand() % 10 == 0) {
                    currentState = HardwareState::ERROR;
                } else {
                    currentState = HardwareState::IDLE;
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            case HardwareState::ERROR:
                SafePrint("Hardware State: ERROR\n");
                currentState = HardwareState::IDLE;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
        }
    }
}

int main() {
    std::ofstream logFile("hardware_states.log", std::ios_base::app | std::ios_base::out);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return 1;
    }

    // Create a mutex to protect the print queue
    std::mutex printMutex;

    // Start a thread to asynchronously write to file
    std::thread printToFileThread(PrintToFileAsync);

    // Simulate the hardware state machine in another thread
    std::thread simulateHardwareThread(SimulateHardwareStateMachine);

    // Main loop to manage user input (optional)
    while (true) {
        char choice;
        std::cout << "Enter 't' to toggle printing, 'q' to quit: ";
        std::cin >> choice;

        switch (choice) {
            case 't':
                g_EnablePrinting = !g_EnablePrinting;
                std::cout << "Printing " << (g_EnablePrinting ? "enabled" : "disabled") << std::endl;
                break;
            case 'q':
                g_EnablePrinting = false;  // Disable printing before exiting
                logFile.close();
                simulateHardwareThread.join();
                printToFileThread.join();
                std::cout << "Program exited." << std::endl;
                return 0;
            default:
                std::cout << "Invalid input. Please try again." << std::endl;
        }
    }

    return 0;
}
