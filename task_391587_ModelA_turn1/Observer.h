#include <iostream>
#include <vector>

class Observer {
public:
    virtual void update() = 0;
};

class ConcreteObserverA : public Observer {
public:
    void update() override {
        // Update logic for Observer A
    }
};

class Subject {
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void notify() {
        for (auto* observer : observers) {
            observer->update();
        }
    }

private:
    std::vector<Observer*> observers;
};
