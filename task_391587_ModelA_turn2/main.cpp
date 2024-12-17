#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <functional>
#include <mutex>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    void registerObserver(Observer* observer) {
        std::lock_guard<std::mutex> lock(observerMutex);
        observers.push_back(observer);
    }

    void notifyObservers() {
        std::lock_guard<std::mutex> lock(observerMutex); 
        for (auto observer : observers) {
            // Launch the observer's update in a separate thread
            std::thread(&Observer::update, observer).detach();
        }
    }

    void doWork() {
        // Simulate work that notifies observers
        std::cout << "Subject is doing work...\n";
        for (int i = 0; i < 10000000; ++i) {
            // Simulate some processing
        }
        notifyObservers();
    }

private:
    std::vector<Observer*> observers;
    std::mutex observerMutex; // To protect observer access
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(int id, Subject* subject) : id(id), subject(subject) {
        subject->registerObserver(this);
    }

    void update() override {
        // Simulate some long-running task 
        std::cout << "Observer " << id << " is processing...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulated work
        std::cout << "Observer " << id << " finished processing.\n";
    }

private:
    int id;
    Subject* subject;
};

int main() {
    Subject subject;

    // Creating observers
    for (int i = 0; i < 5; ++i) {
        new ConcreteObserver(i, &subject);
    }

    // Use the Subject to trigger the notifications
    subject.doWork();

    // Wait for a moment to allow all observer tasks to finish
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
