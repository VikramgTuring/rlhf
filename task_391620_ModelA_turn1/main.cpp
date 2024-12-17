#include <iostream>
#include <vector>
#include <string>

// Observer Interface
class Observer {
public:
    virtual void update(const std::string& data) = 0;
};

// Subject Interface
class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
};

// Concrete Subject
class DataSource : public Subject {
private:
    std::vector<Observer*> observers;
    std::string data;

public:
    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (Observer* observer : observers) {
            observer->update(data);
        }
    }

    void setData(const std::string& newData) {
        data = newData;
        notify();
    }
};

// Concrete Observer
class DataUpdater : public Observer {
private:
    std::string name;

public:
    DataUpdater(const std::string& name) : name(name) {}

    void update(const std::string& data) override {
        std::cout << "Observer " << name << " received data update: " << data << std::endl;
    }
};

// Example Usage
int main() {
    DataSource dataSource;

    DataUpdater observer1("Observer 1");
    DataUpdater observer2("Observer 2");

    dataSource.attach(&observer1);
    dataSource.attach(&observer2);

    dataSource.setData("New data 1"); // Both observers will be notified
    dataSource.setData("New data 2"); // Both observers will be notified

    dataSource.detach(&observer1);    // Detach observer1

    dataSource.setData("New data 3"); // Only observer2 will be notified

    return 0;
}
