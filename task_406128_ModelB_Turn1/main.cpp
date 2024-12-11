#include <iostream>
#include <vector>
#include <string>

// Subject Interface
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notifyAllObservers() = 0;
};

// Concrete Subject: Device
class Device : public Subject {
private:
    std::string name_;
    std::vector<Observer*> observers_;
    int data_ = 0;

public:
    Device(const std::string& name) : name_(name) {}
    
    std::string getName() const { return name_; }
    
    void attach(Observer* observer) override {
        observers_.push_back(observer);
    }
    
    void detach(Observer* observer) override {
        auto it = std::find(observers_.begin(), observers_.end(), observer);
        if (it != observers_.end()) {
            observers_.erase(it);
        }
    }
    
    void notifyAllObservers() override {
        for (auto observer : observers_) {
            observer->update(this);
        }
    }
    
    // Method to generate data for demonstration purposes
    void generateData() {
        data_++;
        std::cout << "Device " << name_ << " generated new data: " << data_ << std::endl;
        notifyAllObservers();
    }
};

// Observer Interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject* subject) = 0;
};

// Concrete Observer: Client
class Client : public Observer {
private:
    std::string name_;
    std::vector<Device*> devices_;

public:
    Client(const std::string& name) : name_(name) {}
    
    void subscribe(Device* device) {
        if (std::find(devices_.begin(), devices_.end(), device) == devices_.end()) {
            devices_.push_back(device);
            device->attach(this);
        }
    }
    
    void unsubscribe(Device* device) {
        if (auto it = std::find(devices_.begin(), devices_.end(), device); it != devices_.end()) {
            devices_.erase(it);
            device->detach(this);
        }
    }
    
    void update(Subject* subject) override {
        Device* device = dynamic_cast<Device*>(subject);
        if (device) {
            std::cout << "Client " << name_ << " received data from Device " << device->getName() << std::endl;
        }
    }

    void checkForNewData() {
        for (Device* device : devices_) {
            device->generateData();
        }
    }
};

// Mediator
class NetworkCoordinator {
private:
    std::vector<Device*> devices_;

public:
    void addDevice(Device* device) {
        devices_.push_back(device);
    }

    void attachClient(Client* client) {
        // Here, you could manage client attachment to the network, but for simplicity,
        // the client directly attaches to devices via the subscribe method.
    }

    Device* getDeviceByName(const std::string& name) {
        for (Device* device : devices_) {
            if (device->getName() == name) {
                return device;
            }
        }
        return nullptr;
    }
};

int main() {
    NetworkCoordinator coordinator;

    Device* tempSensor = new Device("Temperature Sensor");
    Device* motionSensor = new Device("Motion Sensor");

    coordinator.addDevice(tempSensor);
    coordinator.addDevice(motionSensor);
