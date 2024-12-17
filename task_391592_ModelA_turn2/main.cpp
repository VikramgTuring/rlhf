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
    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyAllObservers() {
        for (const auto& observer : observers) {
            observer->update();
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
};

class Subscriber : public Observer {
public:
    void update() override {
        std::cout << "Subscriber notified." << std::endl;
    }
};

int main() {
    Subject subject;

    // Attach observers
    auto observer1 = std::make_shared<Subscriber>();
    auto observer2 = std::make_shared<Subscriber>();

    subject.attach(observer1);
    subject.attach(observer2);

    subject.notifyAllObservers();

    // Removing an observer
    subject.detach(observer1);
    subject.notifyAllObservers();

    return 0;
}
