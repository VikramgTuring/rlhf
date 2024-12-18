#include <chrono>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>

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
        static std::mutex mtx;
        {
            std::lock_guard<std::mutex> lock(mtx);
        }
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
    const int numThreads = 10;

    {
        cout << "Profiling Singleton with " << numThreads << " threads..." << endl;
        auto start = chrono::high_resolution_clock::now();

        vector<thread> threads;
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([&] {
                Singleton::getInstance().doWork();
                });
        }

        for (thread& t : threads) {
            t.join();
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Execution time: " << duration.count() / 1'000'000 << " ms" << endl;
    }

    {
        cout << "Profiling Factory with " << numThreads << " threads..." << endl;
        auto start = chrono::high_resolution_clock::now();

        vector<thread> threads;
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([&] {
                unique_ptr<Worker> worker = Factory::createWorker();
                worker->doWork();
                });
        }

        for (thread& t : threads) {
            t.join();
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Execution time: " << duration.count() / 1'000'000 << " ms" << endl;
    }

    {
        cout << "Profiling Observer with " << numThreads << " threads..." << endl;
        Subject subject;
        vector<ConcreteObserver> observers;
        for (int i = 0; i < numThreads; ++i) {
            observers.emplace_back(&subject);
        }

        auto start = chrono::high_resolution_clock::now();

        vector<thread> threads;
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back([&] {
                subject.doWork();
                });
        }

        for (thread& t : threads) {
            t.join();
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << "Execution time: " << duration.count() / 1'000'000 << " ms" << endl;
    }

