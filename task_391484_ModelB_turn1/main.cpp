#include <iostream>
#include <vector>
#include <string>

#define ENUM_TO_STRING(enum_val) #enum_val

// Forward declaration of EventType enum for type safety in Observer::update
class TestSubject;
enum class EventType;

// Enumeration for different types of events
enum class EventType {
    TEST_CASE_COMPLETION,
    ASSERTION_FAILURE,
    RESOURCE_CLEANUP
};

// Subject (TestSubject) class
class TestSubject {
private:
    std::vector<class Observer*> observers;

public:
    // Attach an observer
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    // Remove an observer
    void detach(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    // Notify all observers about an event
    void notifyAllObservers(EventType event) {
        for (auto observer : observers) {
            observer->update(this, event);
        }
    }

    // Simulate triggering an event
    void triggerTestCaseCompletionEvent() {
        notifyAllObservers(EventType::TEST_CASE_COMPLETION);
    }

    void triggerAssertionFailureEvent() {
        notifyAllObservers(EventType::ASSERTION_FAILURE);
    }

    void triggerResourceCleanupEvent() {
        notifyAllObservers(EventType::RESOURCE_CLEANUP);
    }

    std::string getSubjectName() const {
        return "Test Manager";
    }
};

// Observer base class
class Observer {
public:
    virtual ~Observer() = default;

    // Update method to handle events from the TestSubject
    virtual void update(TestSubject* subject, EventType event) = 0;
};

// Concrete Observer class (TestReporter) that handles events
class TestReporter : public Observer {
public:
    void update(TestSubject* subject, EventType event) override {
        std::cout << "[" << ENUM_TO_STRING(event) << "] " << subject->getSubjectName() << ": ";
        switch (event) {
            case EventType::TEST_CASE_COMPLETION:
                std::cout << "Test case completed." << std::endl;
                break;
            case EventType::ASSERTION_FAILURE:
                std::cout << "Assertion failed." << std::endl;
                break;
            case EventType::RESOURCE_CLEANUP:
                std::cout << "Resource cleanup initiated." << std::endl;
                break;
        }
    }
};

int main() {
    TestSubject testManager;
    TestReporter reporter;

    std::cout << "Registering TestReporter as an observer..." << std::endl;
    testManager.attach(&reporter);

    std::cout << "Simulating events..." << std::endl;
    testManager.triggerTestCaseCompletionEvent();
    testManager.triggerAssertionFailureEvent();
    testManager.triggerResourceCleanupEvent();

    std::cout << "Unregistering observer..." << std::endl;
    testManager.detach(&reporter);

    return 0;
}

