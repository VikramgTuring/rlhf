#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <exception>

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
            try {
                observer->update(status);
            } catch (const std::exception& e) {
                std::cerr << "Exception caught while notifying observer: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "Unknown exception caught while notifying observer." << std::endl;
            }
        }
    }
};

// Concrete Observer classes
class Light : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Light received status update: " << status << std::endl;
        // Simulating normal behavior
    }
};

class Thermostat : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Thermostat received status update: " << status << std::endl;
        // Simulating normal behavior
    }
};

class FaultyObserver : public Observer {
public:
    void update(const std::string& status) override {
        throw std::runtime_error("FaultyObserver encountered an issue!");
    }
};

class SecuritySystem : public Observer {
public:
    void update(const std::string& status) override {
        std::cout << "Security System received status update: " << status << std::endl;
        // Simulating normal behavior
    }
};

int main() {
    CentralDevice centralDevice;

    Light livingRoomLight;
    Thermostat homeThermostat;
    FaultyObserver faultyObserver;  // This observer will throw an exception
    SecuritySystem homeSecurity;

    // Register observers
    centralDevice.addObserver(&livingRoomLight);
    centralDevice.addObserver(&homeThermostat);
    centralDevice.addObserver(&faultyObserver);
    centralDevice.addObserver(&homeSecurity);

    // Simulate status changes
    centralDevice.setStatus("Home is occupied");
    centralDevice.setStatus("Home is unoccupied");

    return 0;
}
