#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <mutex>

// Forward declaration for avoiding circular dependencies
class Observer;

// Subject interface
class Subject {
protected:
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyAllObservers(const std::vector<double>& stockPrices) {
        // Notify observers asynchronously using threads
        std::vector<std::future<void>> futures;
        for (Observer* observer : observers) {
            futures.push_back(std::async(std::launch::async, &Observer::update, observer, std::cref(stockPrices)));
        }
        // Wait for all notification tasks to complete
        for (auto& future : futures) {
            future.get();
        }
    }

    virtual ~Subject() = default;
};

// Observer interface
class Observer {
public:
    virtual void update(const std::vector<double>& data) = 0;
    virtual ~Observer() = default;
};

// Concrete Subject
class StockData : public Subject {
private:
    std::vector<double> stockPrices;

public:
    void setStockPrices(const std::vector<double>& prices) {
        stockPrices = prices;
        notifyAllObservers(stockPrices);
    }

    const std::vector<double>& getStockPrices() const {
        return stockPrices;
    }
};

// Concrete Observer
class StockAnalyzer : public Observer {
private:
    std::string name;

public:
    StockAnalyzer(const std::string& name) : name(name) {}

    void update(const std::vector<double>& stockPrices) override {
        std::cout << name << ": Received stock price updates." << std::endl;
        
        for (const auto& price : stockPrices) {
            std::cout << name << ": Stock price: $" << price << std::endl;
            // Simulate processing delay
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            // Example condition for violation handling
            if (price > 100) {
                std::cout << name << ": Alert! Stock price exceeds $100." << std::endl;
            }
        }
    }
};

int main() {
    StockData stockData;
    StockAnalyzer technicalAnalyzer("Technical Analyst");
    StockAnalyzer fundamentalAnalyzer("Fundamental Analyst");

    stockData.attach(&technicalAnalyzer);
    stockData.attach(&fundamentalAnalyzer);

    // Simulating generating large and complex stock price data
    std::vector<double> prices = { 75.50, 80.25, 102.00, 95.10, 110.75 };

    // Set and notify observers with the new stock prices
    stockData.setStockPrices(prices);

    return 0;
}  
