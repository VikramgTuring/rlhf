#include <iostream>
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update(int value) = 0; // Pure virtual method
};

class Subject {
private:
    std::vector<Observer*> observers;
    int state;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    
    void detach(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setState(int value) {
        state = value;
        notify();
    }

    void notify() {
        for (auto observer : observers) {
            observer->update(state);
        }
    }
};

class ConcreteObserver : public Observer {
public:
    int state;
    
    void update(int value) override {
        state = value; // Update the observer's state
    }
};
