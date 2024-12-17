#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    void registerObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        std::vector<std::future<void>> futures;

        for (auto observer : observers) {
            // Create a future to notify the observer asynchronously
            futures.push_back(std::async(std::launch::async, [observer]() {
                observer->update();
            }));
        }
        
        // Optionally, wait for all notifications to finish
        for (auto& future : futures) {
            future.get(); // You can choose to handle the results if necessary
        }
    }

    void doWork() {
        // Simulate work that notifies observers
        for (int i = 0; i < 10000000; ++i) {
            // Simulate some work
        }
        notifyObservers();
    }

private:
    std::vector<Observer*> observers;
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(Subject* subject) : subject(subject) {
        subject->registerObserver(this);
    }

    void update() override {
        // Simulate a long-running task
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work delay
        std::cout << "Observer notified and completed work." << std::endl;
    }

private:
    Subject* subject;
};

int main() {
    Subject subject;
    const int numObservers = 10;
    for (int i = 0; i < numObservers; ++i) {
        ConcreteObserver observer(&subject);
    }

    subject.doWork();

    return 0;
}
