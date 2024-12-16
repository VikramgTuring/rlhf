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
    virtual void onDataUpdate(int newData) = 0;
};

class Subject {
public:
    void attach(std::shared_ptr<Observer> observer) {
        std::lock_guard<std::mutex> lock(mutex);
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<Observer> observer) {
        std::lock_guard<std::mutex> lock(mutex);
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(int newData) {
        std::lock_guard<std::mutex> lock(mutex);
        for (const auto& observer : observers) {
            observer->onDataUpdate(newData);
        }
    }

private:
    std::vector<std::shared_ptr<Observer>> observers;
    std::mutex mutex; // Mutex to protect observer access
};

class ConcreteObserver : public Observer {
public:
    void onDataUpdate(int newData) override {
        std::cout << "Observer received new data: " << newData << std::endl;
    }
};

class DataStream : public Subject {
public:
    void simulateDataStream() {
        for (int i = 0; i < 10; ++i) {
            notify(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

void attachObserversFromThread(DataStream& dataStream) {
    for (int i = 0; i < 5; ++i) {
        auto observer = std::make_shared<ConcreteObserver>();
        dataStream.attach(observer);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void detachObserversFromThread(DataStream& dataStream) {
    for (int i = 0; i < 3; ++i) {
        auto observer = std::make_shared<ConcreteObserver>();
        dataStream.attach(observer);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        dataStream.detach(observer);
    }
}

int main() {
    DataStream dataStream;

    std::thread attachThread(attachObserversFromThread, std::ref(dataStream));
    std::thread detachThread(detachObserversFromThread, std::ref(dataStream));

    dataStream.simulateDataStream();

    attachThread.join();
    detachThread.join();

    return 0;
}
