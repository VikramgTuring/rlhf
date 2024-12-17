
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <stdexcept>

class Observer {
public:
    virtual void update(const std::vector<double>& stockPrices) = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> observers;
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<std::vector<double>> dataQueue;

public:
    void attach(Observer* observer) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            observers.push_back(observer);
        }
        cv.notify_one();
    }

    void produceData(const std::vector<double>& data) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(data);
        }
        cv.notify_one();
    }

    void consumeData() {
        while (true) {
            std::vector<double> data;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [this]() { return !dataQueue.empty(); });
                data = dataQueue.front();
                dataQueue.pop();
            }

            for (Observer* observer : observers) {
                observer->update(data);
            }
        }
    }

    virtual ~Subject() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push({}); // Notify consumers to exit
        }
        cv.notify_all();
    }
};

class StockData : public Subject {
public:
    void generateAndNotifyData() {
        while (true) {
            // Simulate generating complex and big data
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::vector<double> stockPrices = generateComplexData();
            produceData(stockPrices);
        }
    }

    private:
    std::vector<double> generateComplexData() {
        // Simulate generating complex stock prices data with some latency
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::vector<double> prices = { 80.50, 81.20, 82.89, 84.33, 85.90, ... }; // Replace with actual data generation
        return prices;
    }
};

class StockAnalyzer : public Observer {
private:
    std::string name;

public:
    StockAnalyzer(const std::string& name) : name(name) {}

    void update(const std::vector<double>& stockPrices) override {
        // handle an-analyzer logic
        std::cout << name << ": Processing data chunk..." << std::endl;
        // Simulate analytical task
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Now, perform data analysis ...
        // For demo purposes, we just print the average
        double average = std::accumulate(stockPrices.begin(), stockPrices.end(), 0.0) / stockPrices.size();
        std::cout << name << ": Analyzed average stock price: $" << average << std::endl;
    }
};

int main() {
    StockData stockData;

    // Start background thread to generate and produce data
    std::thread dataProducerThread(&StockData::generateAndNotifyData, &stockData);

    // Start multiple consumers (analyzers)
    for (int i = 0; i < 3; ++i) {
