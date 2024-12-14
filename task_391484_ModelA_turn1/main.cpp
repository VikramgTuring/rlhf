#include <iostream>
#include <vector>
#include <string>
#include <memory>

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

public:
    void attach(std::shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyTestCompleted(const std::string& testName) override {
        for (const auto& observer : observers) {
            observer->onTestCompleted(testName);
        }
    }

    void notifyAssertionFailed(const std::string& testName, const std::string& message) override {
        for (const auto& observer : observers) {
            observer->onAssertionFailed(testName, message);
        }
    }

    void notifyCleanup() override {
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
int main() {
    auto testSuite = std::make_shared<TestSuite>();
    auto logger = std::make_shared<Logger>();

    // Attach the logger observer
    testSuite->attach(logger);

    // Simulate test events
    testSuite->notifyTestCompleted("Test Case 1");
    testSuite->notifyAssertionFailed("Test Case 1", "Expected true but got false");
    testSuite->notifyCleanup();

    return 0;
}
