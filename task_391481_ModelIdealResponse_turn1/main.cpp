#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

// Observer interface
class Observer {
public:
    virtual void update(const std::string& status) = 0;
    virtual ~Observer() = default;
};

// Central Device (Subject)
class CentralDevice {
private:
    std::vector<Observer*> observers;
    std::string status;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setStatus(const std::string& newStatus) {
        status = newStatus;
        notifyObservers();
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update(status);
        }
    }
};

// Concrete Observer classes
class Light : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Light received status update: " << status << std::endl;
        // Additional logic for lights could go here
    }
};

class Thermostat : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Thermostat received status update: " << status << std::endl;
        // Additional logic for thermostat could go here
    }
};

class SecuritySystem : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Security System received status update: " << status << std::endl;
        // Additional logic for security system could go here
    }
};

int main() {
    CentralDevice centralDevice;

    Light livingRoomLight;
    Thermostat homeThermostat;
    SecuritySystem homeSecurity;

    // Register observers
    centralDevice.addObserver(&livingRoomLight);
    centralDevice.addObserver(&homeThermostat);
    centralDevice.addObserver(&homeSecurity);

    // Simulate status changes
    centralDevice.setStatus("Home is occupied");
    centralDevice.setStatus("Home is unoccupied");

    return 0;
}
