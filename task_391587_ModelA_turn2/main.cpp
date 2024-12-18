#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

// Function to measure the execution time of a block of code
template <typename Func>
auto measureTime(Func&& func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count(); // Return in microseconds
}

// Singleton Class
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void doWork() {
        // Simulate work
        for (volatile int i = 0; i < 1000000; ++i) {}
    }

private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

// Factory Class
class Worker {
public:
    virtual void doWork() = 0;
};

class ConcreteWorker : public Worker {
public:
    void doWork() override {
        for (volatile int i = 0; i < 1000000; ++i) {}
    }
};

class Factory {
public:
    static unique_ptr<Worker> createWorker() {
        return make_unique<ConcreteWorker>();
    }
};

// Observer Class
class Observer {
public:
    virtual void update() = 0;
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
        for (volatile int i = 0; i < 1000000; ++i) {}
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
        for (volatile int i = 0; i < 1000000; ++i) {}
    }
private:
    Subject* subject;
};

// Thread function for profiling
template<typename PatternFunc>
void profilePattern(int threadCount, PatternFunc func) {
    vector<thread> threads;
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(func);
    }
    
    for (auto& th : threads) {
        th.join();
    }
}

int main() {
    const int NUM_THREADS = 10;

    {
        cout << "Profiling Singleton with " << NUM_THREADS << " threads..." << endl;
        auto time = measureTime([&] {
            profilePattern(NUM_THREADS, [] {
                Singleton::getInstance().doWork();
            });
        });
        cout << "Execution time: " << time << " microseconds" << endl;
    }

    {
        cout << "Profiling Factory with " << NUM_THREADS << " threads..." << endl;
        auto time = measureTime([&] {
            profilePattern(NUM_THREADS, [] {
                auto worker = Factory::createWorker();
                worker->doWork();
            });
        });
        cout << "Execution time: " << time << " microseconds" << endl;
    }

    {
        cout << "Profiling Observer with " << NUM_THREADS << " threads..." << endl;
        Subject subject;
        ConcreteObserver observer(&subject);
        auto time = measureTime([&] {
            profilePattern(NUM_THREADS, [&subject] {
                subject.doWork();
            });
        });
        cout << "Execution time: " << time << " microseconds" << endl;
    }

    return 0;
}
