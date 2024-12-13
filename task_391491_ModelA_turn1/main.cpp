#include <iostream>
#include <memory>
#include <vector>

// Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;  // Pure virtual function
};

// Concrete command: a command to turn on a light
class LightOnCommand : public Command {
public:
    void execute() override {
        std::cout << "The light is ON\n";
    }
};

// Concrete command: a command to turn off a light
class LightOffCommand : public Command {
public:
    void execute() override {
        std::cout << "The light is OFF\n";
    }
};

// Invoker class: can come with multiple commands
class RemoteControl {
private:
    std::vector<std::shared_ptr<Command>> commandList; // Storing commands with shared_ptr for ownership and safety

public:
    void addCommand(const std::shared_ptr<Command>& command) {
        commandList.push_back(command);
    }

    void pressButton(int index) {
        if (index < commandList.size()) {
            commandList[index]->execute();
        } else {
            std::cout << "Invalid command index!\n";
        }
    }
};

// Client code
int main() {
    RemoteControl remote;

    // Creating commands with type safety using smart pointers
    auto lightOn = std::make_shared<LightOnCommand>();
    auto lightOff = std::make_shared<LightOffCommand>();

    // Adding commands to the remote
    remote.addCommand(lightOn);
    remote.addCommand(lightOff);

    // Executing commands
    remote.pressButton(0); // The light is ON
    remote.pressButton(1); // The light is OFF
    remote.pressButton(2); // Invalid command index!

    return 0;
}
