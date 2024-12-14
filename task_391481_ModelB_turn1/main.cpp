#include <iostream>

class Observer {
public:
    virtual ~Observer() = default;

    // Method called by the subject when it updates
    virtual void update() = 0;
};

#include <vector>

class Subject {
public:
    void attach(Observer* observer) { observers.push_back(observer); }
    void detach(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
    void notifyAll() {
        for (auto observer : observers) {
            observer->update();
        }
    }

    void setStatus(const std::string& status) {
        this->status = status;
        notifyAll();
    }

    std::string getStatus() const { return status; }

private:
    std::string status;
    std::vector<Observer*> observers;
};

class Light : public Observer {
public:
    Light(Subject* centralDevice) {
        centralDevice->attach(this);
        name = "Light";
    }

    ~Light() override {
        // Detach the observer when it is destroyed
        auto centralDevice = dynamic_cast<Subject*>(getSubject());
        if (centralDevice) {
            centralDevice->detach(this);
        }
    }

    void update() override {
        std::cout << "\t" << name << ": Status changed to " << centralDevice->getStatus() << std::endl;
    }

    Subject* getSubject() const { return subject; }

private:
    std::string name;
    Subject* subject = nullptr;
};

class Thermostat : public Observer {
public:
    Thermostat(Subject* centralDevice) {
        centralDevice->attach(this);
        name = "Thermostat";
    }

    ~Thermostat() override {
        auto centralDevice = dynamic_cast<Subject*>(getSubject());
        if (centralDevice) {
            centralDevice->detach(this);
        }
    }

    void update() override {
        std::cout << "\t" << name << ": Status changed to " << centralDevice->getStatus() << std::endl;
    }

    Subject* getSubject() const { return subject; }

private:
    std::string name;
    Subject* subject = nullptr;
};

int main() {
    Subject centralDevice;

    Light light(&centralDevice);
    Thermostat thermostat(&centralDevice);

    std::cout << "Initial status:" << std::endl;

    centralDevice.setStatus("On");
    centralDevice.setStatus("Off");
    centralDevice.setStatus("Warning");

    return 0;
}
