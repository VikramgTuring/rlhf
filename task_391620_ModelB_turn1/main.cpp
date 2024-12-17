
#include <iostream>
#include <vector>
#include <string>

class Observer {
public:
    virtual void update(const double& stockPrice) = 0;
    virtual ~Observer() = default;
};

class Subject {
protected:
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyAllObservers(const double& stockPrice) {
        for (Observer* observer : observers) {
            observer->update(stockPrice);
        }
    }

    virtual ~Subject() = default;
};

class StockData : public Subject {
private:
    double stockPrice;

public:
    void setStockPrice(const double& price) {
        stockPrice = price;
        notifyAllObservers(stockPrice);
    }

    double getStockPrice() const {
        return stockPrice;
    }
};

class StockAnalyzer : public Observer {
private:
    std::string name;

public:
    StockAnalyzer(const std::string& name) : name(name) {}

    void update(const double& stockPrice) override {
        std::cout << name << ": Stock price updated to: $" << stockPrice << std::endl;
        // Perform your analysis here
        if (stockPrice > 100) {
            std::cout << name << ": Alert! Stock price exceeds $100." << std::endl;
        }
    }
};

int main() {
    StockData stockData;
    StockAnalyzer technicalAnalyzer("Technical Analyst");
    StockAnalyzer fundamentalAnalyzer("Fundamental Analyst");

    stockData.attach(&technicalAnalyzer);
    stockData.attach(&fundamentalAnalyzer);

    stockData.setStockPrice(80.50);
    stockData.setStockPrice(105.75);

    return 0;
}  

