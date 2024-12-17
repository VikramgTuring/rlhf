#include <iostream>
#include <vector>
#include <memory>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Subject {
public:
    void attach(std::unique_ptr<Observer> observer) {
        observers.push_back(std::move(observer));
    }

    void notifyAllObservers() {
        for (const auto& observer : observers) {
            observer->update();
        }
    }

    void processEvent() {
        std::cout << "Event generated." << std::endl;
        notifyAllObservers();
    }

private:
    std::vector<std::unique_ptr<Observer>> observers;
};

class Subscriber1 : public Observer {
public:
    Subscriber1(Subject& subject) {
        subject.attach(std::make_unique<Subscriber1>(*this));
    }

    void update() override {
        std::cout << "Subscriber1: Event received." << std::endl;
    }
};

class Subscriber2 : public Observer {
public:
    Subscriber2(Subject& subject) {
        subject.attach(std::make_unique<Subscriber2>(*this));
    }

    void update() override {
        std::cout << "Subscriber2: Event received." << std::endl;
    }
};

int main() {
    Subject eventSource;
    Subscriber1 subscriber1(eventSource);
    Subscriber2 subscriber2(eventSource);

    eventSource.processEvent();
    return 0;
}
