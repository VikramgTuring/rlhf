#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Observer {
public:
    virtual ~Observer() {}
    virtual void onDataUpdate(int newData) = 0; // Interface for data update
};

class Subject {
public:
    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(int newData) {
        for (const auto& observer : observers) {
            observer->onDataUpdate(newData); // Notify each observer
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers; // List of observers
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

    dataStream.simulateDataStream(); // Start simulating the data stream
    return 0;
}
