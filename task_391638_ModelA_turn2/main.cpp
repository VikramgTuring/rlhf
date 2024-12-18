#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <functional>

// Observer Interface
class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update(const std::string& message) = 0;
};

// Subject Interface
class ISubject {
public:
    virtual ~ISubject() {}
    virtual void subscribe(IObserver* observer) = 0;
    virtual void unsubscribe(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Notification struct to hold message and priority
struct Notification {
    std::string message;
    int priority;

    // Constructor
    Notification(const std::string& msg, int pri) : message(msg), priority(pri) {}

    // To make Notification sortable by priority
    bool operator<(const Notification& other) const {
        return priority < other.priority; // Lower number means higher priority (e.g., 1 is higher than 2)
    }
};

// Concrete Subject
class NotificationSystem : public ISubject {
private:
    std::vector<IObserver*> observers;
    std::priority_queue<Notification> notifications; // Priority queue to handle notifications

public:
    void subscribe(IObserver* observer) override {
        observers.push_back(observer);
    }

    void unsubscribe(IObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void addNotification(const std::string& message, int priority) {
        notifications.emplace(message, priority); // Add notification with priority
    }

    void notifyObservers() override {
        while (!notifications.empty()) {
            Notification notification = notifications.top(); // Get the highest priority notification
            notifications.pop(); // Remove it from the queue

            for (IObserver* observer : observers) {
                observer->update(notification.message);
            }
        }
    }
};

// Concrete Observer
class User : public IObserver {
private:
    std::string name;

public:
    User(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << "User " << name << " received notification: " << message << std::endl;
    }
};

// Example usage
int main() {
    NotificationSystem notificationSystem;

    User user1("Alice");
    User user2("Bob");
    User user3("Charlie");

    notificationSystem.subscribe(&user1);
    notificationSystem.subscribe(&user2);
    notificationSystem.subscribe(&user3);

    // Adding notifications with different priorities
    notificationSystem.addNotification("Critical error occurred!", 1); // High priority
    notificationSystem.addNotification("New message from your friend.", 3); // Medium priority
    notificationSystem.addNotification("Your profile has been updated.", 2); // Medium priority
    notificationSystem.addNotification("Reminder: Meeting at 3 PM.", 4); // Low priority

    // Notify observers with priority order
    notificationSystem.notifyObservers();

    return 0;
}
