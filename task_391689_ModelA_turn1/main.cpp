#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    virtual void notifyObservers(const std::string& message) = 0;
};

// Concrete Subject
class NotificationSystem : public ISubject {
private:
    std::vector<IObserver*> observers;

public:
    void subscribe(IObserver* observer) override {
        observers.push_back(observer);
    }

    void unsubscribe(IObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const std::string& message) override {
        for (IObserver* observer : observers) {
            observer->update(message);
        }
    }

    // Method to simulate generating notifications
    void generateNotification(const std::string& message) {
        std::cout << "Notification generated: " << message << std::endl;
        notifyObservers(message);
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

    notificationSystem.generateNotification("New message received!");
    notificationSystem.generateNotification("Your profile has been updated!");

    // Unsubscribe Bob and send another notification
    notificationSystem.unsubscribe(&user2);
    notificationSystem.generateNotification("You have a new friend request!");

    return 0;
}
