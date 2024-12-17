#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Forward declaration
class Observer;

// Subject interface
class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

// Observer interface
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(const std::string& message) = 0;
};

class ConcreteSubject : public Subject {
private:
    std::vector<Observer*> observers;
    std::string state;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(state);
        }
    }

    void setState(const std::string& newState) {
        state = newState;
        notify();
    }

    std::string getState() const {
        return state;
    }
};

class ConcreteObserver : public Observer {
private:
    std::string name;

public:
    ConcreteObserver(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << "Observer " << name << " received update: " << message << std::endl;
    }
};

int main() {
    ConcreteSubject subject;

    ConcreteObserver observer1("Observer1");
    ConcreteObserver observer2("Observer2");

    // Attach observers to the subject
    subject.attach(&observer1);
    subject.attach(&observer2);

    // Simulate state changes
    subject.setState("Event 1 occurred!");
    subject.setState("Event 2 occurred!");

    // Detach one observer
    subject.detach(&observer1);

    // Simulate another event
    subject.setState("Event 3 occurred!");

    return 0;
}
