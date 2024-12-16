#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <thread>

// Observer Interface
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onTestCompleted(const std::string& testName) = 0;
    virtual void onAssertionFailed(const std::string& testName, const std::string& message) = 0;
    virtual void onCleanup() = 0;
};

// Subject Interface
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notifyTestCompleted(const std::string& testName) = 0;
    virtual void notifyAssertionFailed(const std::string& testName, const std::string& message) = 0;
    virtual void notifyCleanup() = 0;
};

// Concrete Subject
class TestSuite : public ISubject {
private:
    std::vector<std::shared_ptr<IObserver>> observers;
    std::mutex mutex_; // Mutex for thread safety

public:
    void attach(std::shared_ptr<IObserver> observer) override {
        std::lock_guard<std::mutex> lock(mutex_); // Lock for the duration of the function
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver> observer) override {
        std::lock_guard<std::mutex> lock(mutex_); // Lock for the duration of the function
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyTestCompleted(const std::string& testName) override {
        std::lock_guard<std::mutex> lock(mutex_); // Lock for the duration of the notification loop
        for (const auto& observer : observers) {
            observer->onTestCompleted(testName);
        }
    }

    void notifyAssertionFailed(const std::string& testName, const std::string& message) override {
        std::lock_guard<std::mutex> lock(mutex_); // Lock for the duration of the notification loop
        for (const auto& observer : observers) {
            observer->onAssertionFailed(testName, message);
        }
    }

    void notifyCleanup() override {
        std::lock_guard<std::mutex> lock(mutex_); // Lock for the duration of the notification loop
        for (const auto& observer : observers) {
            observer->onCleanup();
        }
    }
};

// Concrete Observer
class Logger : public IObserver {
public:
    void onTestCompleted(const std::string& testName) override {
        std::cout << "Test completed: " << testName << std::endl;
    }

    void onAssertionFailed(const std::string& testName, const std::string& message) override {
        std::cout << "Assertion failed in test " << testName << ": " << message << std::endl;
    }

    void onCleanup() override {
        std::cout << "Resources cleaned up." << std::endl;
    }
};

// Example usage
void simulateTest(TestSuite& testSuite, const std::string& testName) {
    // Simulate some operations
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    testSuite.notifyTestCompleted(testName);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    testSuite.notifyAssertionFailed(testName, "Example assertion failure message");
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    testSuite.notifyCleanup();
}

int main() {
    auto testSuite = std::make_shared<TestSuite>();
    auto logger = std::make_shared<Logger>();

    // Attach the logger observer
    testSuite->attach(logger);

    // Simulating concurrent test execution
    std::thread t1(simulateTest, std::ref(*testSuite), "Test Case 1");
    std::thread t2(simulateTest, std::ref(*testSuite), "Test Case 2");

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}
