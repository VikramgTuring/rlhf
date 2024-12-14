#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

class Subject {
public:
    using ObserverPtr = std::shared_ptr<Observer>;

    void registerObserver(ObserverPtr observer) {
        observers.push_back(observer);
    }

    void removeObserver(ObserverPtr observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyObservers() const {
        for (const ObserverPtr& observer : observers) {
            observer->update();
        }
    }

    void generateData() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            double newData = generateRandomData();
            std::cout << "New data generated: " << newData << std::endl;
            notifyObservers();
        }
    }

private:
    std::vector<ObserverPtr> observers;

    double generateRandomData() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 100.0);
        return dis(gen);
    }
};

class Observer {
public:
    explicit Observer(Subject& subject) : subject(subject) {
        subject.registerObserver(shared_from_this());
    }

    virtual ~Observer() {
        subject.removeObserver(shared_from_this());
    }

    virtual void update() = 0;

private:
    Subject& subject;
};

class DataProcessor : public Observer {
public:
    DataProcessor(Subject& subject) : Observer(subject) {}

    void update() override {
        double newData = subject.getLatestData();
        processData(newData);
    }

private:
    void processData(double data) const {
        std::cout << "DataProcessor: Processing data: " << data << std::endl;
    }
};

int main() {
    Subject dataSource;
    DataProcessor dataProcessor(dataSource);

    std::thread dataGeneratorThread(&Subject::generateData, &dataSource);

    dataGeneratorThread.join();

    return 0;
}
