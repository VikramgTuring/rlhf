#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <condition_variable>

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

// Concrete Subject with Thread Safety
class TestSuite : public ISubject {
private:
    std::mutex mutex_;
    std::condition_variable cv_;
    std::vector<std::shared_ptr<IObserver>> observers_;

public:
    void attach(std::shared_ptr<IObserver> observer) override {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            observers_.push_back(observer);
        }
        cv_.notify_one();
    }

    void detach(std::shared_ptr<IObserver> observer) override {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            auto it = std::remove(observers_.begin(), observers_.end(), observer);
            observers_.erase(it, observers_.end());
        }
        cv_.notify_one();
    }

    void notifyTestCompleted(const std::string& testName) override {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            for (const auto& observer : observers_) {
                observer->onTestCompleted(testName);
            }
        }
        cv_.notify_all();
    }

    void notifyAssertionFailed(const std::string& testName, const std::string& message) override {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            for (const auto& observer : observers_) {
                observer->onAssertionFailed(testName, message);
            }
        }
        cv_.notify_all();
    }

    void notifyCleanup() override {
        {
            std::unique_lock<std::mutex> lock(mutex_);
            for (const auto& observer : observers_) {
                observer->onCleanup();
            }
        }
        cv_.notify_all();
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

// Example usage with concurrent tests
int main() {
    auto testSuite = std::make_shared<TestSuite>();
    auto logger = std::make_shared<Logger>();

    // Attach the logger observer from another thread
    std::thread attachThread([testSuite, logger] {
        testSuite->attach(logger);
    });

    // Simulate test events from another thread
    std::thread eventThread([testSuite] {
        testSuite->notifyTestCompleted("Test Case 1");
        testSuite->notifyAssertionFailed("Test Case 2", "Expected true but got false");
        testSuite->notifyCleanup();
    });

    attachThread.join();
    eventThread.join();

    return 0;
}
