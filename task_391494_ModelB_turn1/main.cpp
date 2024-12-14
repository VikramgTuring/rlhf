#include <iostream>
#include <mutex>
#include <thread>

class Singleton {
private:
    static Singleton* instance;
    static std::mutex mtx;
    int data;

    Singleton() : data(0) {}

public:
    static Singleton* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Singleton;
        }
        return instance;
    }

    void increment() {
        for (int i = 0; i < 1000000; ++i) {
            data++;
        }
    }

    ~Singleton() {
        delete instance;
        instance = nullptr;
    }
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mtx;

int main() {
    const int numThreads = 100;
    std::thread threads[numThreads];

    // Start multiple threads to access the Singleton
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread([]{
            Singleton* singleton = Singleton::getInstance();
            singleton->increment();
        });
    }

    // Join all threads
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // Output the final value of data in the Singleton
    std::cout << "Final value of Singleton::data: " << Singleton::getInstance()->data << std::endl;

    return 0;
};
