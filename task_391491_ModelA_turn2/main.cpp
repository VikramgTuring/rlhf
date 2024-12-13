#include <iostream>
#include <memory>
#include <vector>

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual bool execute() = 0;  // Modified to return success/failure
};

// Concrete command: a command to turn on a light
class LightOnCommand : public Command {
public:
    bool execute() override {
        std::cout << "The light is ON\n";
        return true; // Assume success
    }
};

// Concrete command: a command to turn off a light
class LightOffCommand : public Command {
public:
    bool execute() override {
        std::cout << "The light is OFF\n";
        return true; // Assume success
    }
};

// Composite command: executes a list of commands in sequence
class CompositeCommand : public Command {
private:
    std::vector<std::shared_ptr<Command>> commands;

public:
    void addCommand(const std::shared_ptr<Command>& command) {
        commands.push_back(command);
    }

    bool execute() override {
        for (const auto& command : commands) {
            if (!command->execute()) {
                std::cout << "Command failed, halting execution.\n";
                return false; // Stop execution on failure
            }
        }
        return true; // All commands succeeded
    }
};

// Client code
int main() {
    // Create individual commands
    auto lightOn = std::make_shared<LightOnCommand>();
    auto lightOff = std::make_shared<LightOffCommand>();

    // Create a composite command
    CompositeCommand sequence;
    sequence.addCommand(lightOn);
    sequence.addCommand(lightOff);

    // Execute the sequence
    if (!sequence.execute()) {
        std::cout << "One or more commands failed.\n";
    } else {
        std::cout << "All commands executed successfully.\n";
    }

    return 0;
}
