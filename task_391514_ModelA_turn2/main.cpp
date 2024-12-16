#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

class Observer {
public:
    virtual ~Observer() {}
    virtual void onDataUpdate(int newData) = 0; // Interface for data update
};

class Subject {
public:
    void attach(std::shared_ptr<Observer> observer) {
        std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex for thread safety
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) {
        std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex for thread safety
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(int newData) {
        std::lock_guard<std::mutex> lock(mutex_); // Lock while copying observers
        for (const auto& observer : observers) {
            observer->onDataUpdate(newData); // Notify each observer
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers; // List of observers
    mutable std::mutex mutex_; // Mutex to protect observers
};

// Concrete Observer Example
class ConcreteObserver : public Observer {
public:
    void onDataUpdate(int newData) override {
        std::cout << "Observer received new data: " << newData << std::endl;
    }
};

// Example Subject Sending Data
class DataStream : public Subject {
public:
    void simulateDataStream() {
        // Simulating high-frequency data updates
        for (int i = 0; i < 10; ++i) {
            notify(i); // Notify observers with new data
            // Simulate a delay for demonstration purposes
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

int main() {
    DataStream dataStream;

    auto observer1 = std::make_shared<ConcreteObserver>();
    auto observer2 = std::make_shared<ConcreteObserver>();

    dataStream.attach(observer1);
    dataStream.attach(observer2);

    // Create threads that simulate data streaming
    std::thread dataThread([&dataStream]() {
        dataStream.simulateDataStream(); // Start simulating the data stream
    });

    // Simulate dynamic attachment/detachment in another thread
    std::thread dynamicThread([&dataStream, observer1, observer2]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        dataStream.detach(observer1); // Detach observer1 after some time

        // Simulating another observer
        auto observer3 = std::make_shared<ConcreteObserver>();
        dataStream.attach(observer3); // Attach a new observer
    });

    // Wait for both threads to finish
    dataThread.join();
    dynamicThread.join();

    return 0;
}
