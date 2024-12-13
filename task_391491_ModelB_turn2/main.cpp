#include <iostream>
#include <memory>
#include <vector>
#include <optional>

// Enum to represent command status
enum class CommandStatus {
    Success,
    Failure
};

// Command interface with status
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;

    // Method to check the status of the command
    virtual CommandStatus getStatus() const {
        return CommandStatus::Success; // Base implementation: Assume success
    }
};

// Concrete command: a command to turn on a light
class LightOnCommand : public Command {
public:
    void execute() override {
        std::cout << "The light is ON\n";
    }
};

// Concrete command: a command to turn off a light.
// This command may fail if the light is already off.
class LightOffCommand : public Command {
public:
    void execute() override {
        if (lightIsOn) {
            std::cout << "The light is OFF\n";
            status = CommandStatus::Success;
        } else {
            std::cout << "Light is already off.\n";
            status = CommandStatus::Failure;
        }
    }

    CommandStatus getStatus() const override {
        return status;
    }

private:
    bool lightIsOn = true; // Assume light is on initially
    CommandStatus status = CommandStatus::Success;
};

// Command sequence manager
class CommandSequence {
public:
    void addCommand(const std::shared_ptr<Command>& command) {
        commands.push_back(command);
    }

    void addDependency(size_t dependentIndex, size_t dependencyIndex) {
        if (dependentIndex >= commands.size() || dependencyIndex >= commands.size()) {
            std::cerr << "Invalid command indices!\n";
            return;
        }
        commandDependencies[dependentIndex].push_back(dependencyIndex);
    }

    void executeSequence() {
        for (size_t i = 0; i < commands.size(); ++i) {
            bool canExecute = true;
            for (size_t depIndex : commandDependencies[i]) {
                if (commands[depIndex]->getStatus() == CommandStatus::Failure) {
                    std::cout << "Command " << i << " not executed due to dependency failure.\n";
                    canExecute = false;
                    break;
                }
            }

            if (canExecute) {
                commands[i]->execute();
            }
        }
    }

private:
    std::vector<std::shared_ptr<Command>> commands;
    // Map to store dependencies: index -> vector of dependency indices
    std::unordered_map<size_t, std::vector<size_t>> commandDependencies;
};

// Client code
int main() {
    CommandSequence sequence;

    auto lightOn = std::make_shared<LightOnCommand>();
    auto lightOff = std::make_shared<LightOffCommand>();

    sequence.addCommand(lightOn);
    sequence.addCommand(lightOff);

    // Add dependency: LightOffCommand depends on LightOnCommand success
    sequence.addDependency(1, 0);

    sequence.executeSequence(); // Output: The light is ON, The light is OFF

    lightOff->execute(); // Output: Light is already off.
    sequence.executeSequence(); // Output: The light is ON (LightOffCommand not executed)

    return 0;
}
