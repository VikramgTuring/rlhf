#include <chrono>
#include <iostream>

using namespace std;

// Function to measure the execution time of a block of code
template <typename Func>
auto measureTime(Func&& func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    return duration.count() / 1'000'000; // Return in milliseconds
}
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void doWork() {
        // Simulate work
        for (int i = 0; i < 10000000; ++i) {
        }
    }

private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
class Worker {
public:
    virtual void doWork() = 0;
    virtual ~Worker() = default;
};

class ConcreteWorker : public Worker {
public:
    void doWork() override {
        for (int i = 0; i < 10000000; ++i) {
        }
    }
};

class Factory {
public:
    static unique_ptr<Worker> createWorker() {
        return make_unique<ConcreteWorker>();
    }
};
class Subject {
public:
    void registerObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        for (auto observer : observers) {
            observer->update();
        }
    }

    void doWork() {
        // Simulate work that notifies observers
        for (int i = 0; i < 10000000; ++i) {
        }
        notifyObservers();
    }

private:
    vector<Observer*> observers;
};

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(Subject* subject) : subject(subject) {
        subject->registerObserver(this);
    }

    void update() override {
        // Observe and do work
        for (int i = 0; i < 1000000; ++i) {
        }
    }

private:
    Subject* subject;
};
int main() {
    {
        cout << "Profiling Singleton..." << endl;
        auto time = measureTime([&] {
            Singleton& singleton = Singleton::getInstance();
            singleton.doWork();
        });
        cout << "Execution time: " << time << " ms" << endl;
    }

    {
        cout << "Profiling Factory..." << endl;
        auto time = measureTime([&] {
            unique_ptr<Worker> worker = Factory::createWorker();
            worker->doWork();
        });
        cout << "Execution time: " << time << " ms" << endl;
    }

    {
        cout << "Profiling Observer..." << endl;
        Subject subject;
        ConcreteObserver observer(&subject);
        auto time = measureTime([&] {
            subject.doWork();
        });
        cout << "Execution time: " << time << " ms" << endl;
    }

    return 0;
}
