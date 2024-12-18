#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <thread>

#define LOG_INFO(msg) (std::cout << "INFO: " << msg << std::endl)
#define LOG_ERROR(msg) (std::cout << "ERROR: " << msg << std::endl)

// Logger - Decorator Pattern
class Logger {
public:
    Logger(std::shared_ptr<Logger> next = nullptr) : next_(next) {}

    void log(const std::string& message) {
        LOG_INFO(message);
        if (next_) {
            next_->log(message);
        }
    }

private:
    std::shared_ptr<Logger> next_;
};

class NullLogger : public Logger {
public:
    void log(const std::string&) override {}
};

// Authenticator - Decorator Pattern
class Authenticator {
public:
    Authenticator(std::shared_ptr<Authenticator> next = nullptr) : next_(next) {}

    void authenticate(const std::string& user) {
        if (user == "valid_user") {
            if (next_) {
                next_->authenticate(user);
            }
        } else {
            LOG_ERROR("Authentication failed for user: " + user);
            throw std::runtime_error("Authentication failed");
        }
    }

private:
    std::shared_ptr<Authenticator> next_;
};

class NullAuthenticator : public Authenticator {
public:
    void authenticate(const std::string&) override {}
};

// Transaction - Template Method Pattern
class Transaction {
public:
    template<typename T>
    T execute(T(*function)()) {
        try {
            std::cout << "Transaction Started..." << std::endl;
            auto result = function();
            std::cout << "Transaction Committed" << std::endl;
            return result;
        } catch (...) {
            std::cout << "Transaction Rolled Back" << std::endl;
            throw;
        }
    }
};

// Order Manager
class OrderManager {
public:
    void placeOrder(const std::string& user, double orderAmount) {
        auto authenticator = std::make_shared<Authenticator>(std::make_shared<NullAuthenticator>());
        auto logger = std::make_shared<Logger>(std::make_shared<NullLogger>());

        setAuthenticator(authenticator);
        setLogger(logger);

        try {
            authenticator->authenticate(user);

            Transaction transaction;
            transaction.execute<void>([]() {
                this->processOrder(orderAmount);
            });
        } catch (const std::exception& e) {
            logger->log("Error placing order: " + e.what());
        }
    }

private:
    void processOrder(double amount) {
        std::cout << "Processing order for amount: $" << amount << std::endl;
        logger_->log("Order processed successfully");
    }

    std::shared_ptr<Authenticator> authenticator_;
    std::shared_ptr<Logger> logger_;

    void setAuthenticator(std::shared_ptr<Authenticator> authenticator) {
        authenticator_ = authenticator;
    }

    void setLogger(std::shared_ptr<Logger> logger) {
        logger_ = logger;
    }
};

// Example usage:
int main() {
    OrderManager manager;

    manager.placeOrder("valid_user", 100.0);
    // Output:
    // Transaction Started...
    // Authenticating user: valid_user
    // Processing order for amount: $100
    // Transaction Committed
    // Order processed successfully

    manager.placeOrder("invalid_user", 50.0);
    // Output:
    // Transaction Started...
    // Authenticating user: invalid_user
    // ERROR: Authentication failed for user: invalid_user
    // Transaction Rolled Back

    return 0;
}
