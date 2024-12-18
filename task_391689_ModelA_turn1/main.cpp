#include <iostream>
#include <fstream>
#include <mutex>

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance; // Guaranteed to be destroyed.
        return instance;         // Instantiated on first use.
    }

    void log(const std::string& message) {
        std::lock_guard<std::mutex> guard(mutex_);
        std::ofstream logFile("log.txt", std::ios_base::app);
        logFile << message << std::endl;
    }

private:
    Logger() {} // Constructor is private
    Logger(const Logger&) = delete; // Prevent copying
    Logger& operator=(const Logger&) = delete; // Prevent assignment
    std::mutex mutex_;
};

// Usage
void processOrder(const std::string& orderID) {
    Logger::getInstance().log("Processing order: " + orderID);
    // Further processing logic...
}

class Order {
public:
    virtual void placeOrder(const std::string& orderID) = 0;
};

class RealOrder : public Order {
public:
    void placeOrder(const std::string& orderID) override {
        std::cout << "Order placed: " << orderID << std::endl;
    }
};

class SecurityProxy : public Order {
private:
    RealOrder realOrder;
public:
    void placeOrder(const std::string& orderID) override {
        if (isUserAuthenticated()) {
            realOrder.placeOrder(orderID);
        } else {
            std::cout << "Access Denied: User is not authenticated." << std::endl;
        }
    }

    bool isUserAuthenticated() {
        // Simulate user authentication check
        return true; // Assuming user is authenticated for example
    }
};

// Usage
void placeNewOrder(const std::string& orderID) {
    SecurityProxy proxy;
    proxy.placeOrder(orderID);
}

#include <list>

class Observer {
public:
    virtual void update(const std::string& orderID) = 0;
};

class TransactionManager {
private:
    std::list<Observer*> observers;
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        observers.remove(observer);
    }

    void notify(const std::string& orderID) {
        for (auto& observer : observers) {
            observer->update(orderID);
        }
    }

    void commitTransaction(const std::string& orderID) {
        // Commit the transaction logic...
        notify(orderID);
    }
};

class EmailNotification : public Observer {
public:
    void update(const std::string& orderID) override {
        std::cout << "Sending email notification for order: " << orderID << std::endl;
    }
};

// Usage
void processTransaction(const std::string& orderID) {
    TransactionManager tm;
    EmailNotification emailNotifier;

    tm.attach(&emailNotifier);
    tm.commitTransaction(orderID);
}

int main() {
    std::string orderID = "ORD123";

    // Logging the order process
    processOrder(orderID);

    // Placing a new order with security check
    placeNewOrder(orderID);

    // Processing a transaction with notifications
    processTransaction(orderID);

    return 0;
}
