#include <iostream>
#include <string>
#include "logger.h"

// Define states
enum class HardwareState {
    INITIALIZING,
    RUNNING,
    ERROR,
    SHUTDOWN
};

// Function to simulate state transition
void transitionState(HardwareState& currentState, HardwareState newState, Logger& logger) {
    logger.log("Transitioning from " + std::to_string(static_cast<int>(currentState)) +
               " to " + std::to_string(static_cast<int>(newState)));
    currentState = newState;
}

int main() {
    Logger logger("hardware_log.txt");

    HardwareState currentState = HardwareState::INITIALIZING;

    // Sample state transitions
    transitionState(currentState, HardwareState::RUNNING, logger);
    transitionState(currentState, HardwareState::ERROR, logger);
    transitionState(currentState, HardwareState::SHUTDOWN, logger);

    return 0;
}
