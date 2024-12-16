#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

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
        for (auto observer : observers) {
            try {
                observer->update(status);
            } catch (const std::exception& e) {
                std::cerr << "Error notifying observer: " << e.what() << std::endl;
                auto it = std::find(observers.begin(), observers.end(), observer);
                if (it != observers.end()) {
                    observers.erase(it);
                }
            }
        }
    }
};

// Concrete Observer classes
class Light : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Light received status update: " << status << std::endl;
    }
};

class Thermostat : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Thermostat received status update: " << status << std::endl;
    }
};

class FaultySecuritySystem : public Observer {
public:
    void update(const std::string& status) override {
        throw std::runtime_error("FaultySecuritySystem failed to update!");
    }
};

class SecuritySystem : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Security System received status update: " << status << std::endl;
    }
};

int main() {
    CentralDevice centralDevice;

    Light livingRoomLight;
    Thermostat homeThermostat;
    FaultySecuritySystem faultySecurity;
    SecuritySystem homeSecurity;

    // Register observers
    centralDevice.addObserver(&livingRoomLight);
    centralDevice.addObserver(&homeThermostat);
    centralDevice.addObserver(&faultySecurity);
    centralDevice.addObserver(&homeSecurity);

    // Simulate status changes
    centralDevice.setStatus("Home is occupied");
    centralDevice.setStatus("Home is unoccupied");

    return 0;
}
