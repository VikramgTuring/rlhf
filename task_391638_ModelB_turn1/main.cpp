#include <iostream>
#include <string>
#include <vector>

class Subject {
protected:
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                return;
            }
        }
    }

    void notifyAll() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
};

class Observer {
protected:
    Subject* subject;
    std::string name;

public:
    Observer(Subject* subject, const std::string& name) : subject(subject), name(name) {
        subject->attach(this);
    }

    virtual ~Observer() {
        subject->detach(this);
    }

    virtual void update() {
        std::cout << name << ": Received notification." << std::endl;
    }
};

class UserNotification : public Observer {
public:
    UserNotification(Subject* subject, const std::string& name) : Observer(subject, name) {}

    void update() override {
        std::cout << name << ": Critical User Notification! Processing..." << std::endl;
        // Simulate critical notification processing
        // For example, send an email, display a pop-up, etc.
    }
};

int main() {
    Subject* notificationCenter = new Subject();

    UserNotification* userNotification1 = new UserNotification(notificationCenter, "User A");
    UserNotification* userNotification2 = new UserNotification(notificationCenter, "User B");

    // Simulate triggering a critical event
    notificationCenter->notifyAll();

    delete userNotification1;
    delete userNotification2;
    delete notificationCenter;

    return 0;
}
