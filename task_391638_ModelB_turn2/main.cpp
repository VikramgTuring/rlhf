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

// Concrete Subject
class NotificationSystem : public ISubject {
private:
    enum class Priority {
        HIGH,
        MEDIUM,
        LOW
    };

    std::queue<std::pair<Priority, std::string>> notifications;
    std::vector<IObserver*> observers;

public:
    void subscribe(IObserver* observer) override {
        observers.push_back(observer);
    }

    void unsubscribe(IObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Method to add notifications with priority
    void generateNotification(const std::string& message, Priority priority) {
        notifications.emplace(priority, message);
    }

    void notifyObservers() override {
        while (!notifications.empty()) {
            auto [priority, message] = notifications.front();
            notifications.pop();
            std::cout << "Notification generated: " << message << std::endl;
            for (IObserver* observer : observers) {
                observer->update(message);
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

    notificationSystem.subscribe(&user1);
    notificationSystem.subscribe(&user2);

    notificationSystem.generateNotification("Low priority task completed.", NotificationSystem::Priority::LOW);
    notificationSystem.generateNotification("High priority alert: System malfunction!", NotificationSystem::Priority::HIGH);
    notificationSystem.generateNotification("Medium priority message: Server update available.", NotificationSystem::Priority::MEDIUM);
    notificationSystem.generateNotification("Low priority message: Weather forecast updated.", NotificationSystem::Priority::LOW);
    notificationSystem.generateNotification("Medium priority task completed.", NotificationSystem::Priority::MEDIUM);

    notificationSystem.notifyObservers();

    return 0;
}
