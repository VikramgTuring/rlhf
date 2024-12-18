#include <iostream>
#include <string>
#include <memory>

class Order {
public:
    Order(const std::string& id, const std::string& details)
        : id_(id), details_(details) {}

    std::string getId() const { return id_; }
    std::string getDetails() const { return details_; }

private:
    std::string id_;
    std::string details_;
};
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class ProcessOrderCommand : public Command {
public:
    ProcessOrderCommand(std::shared_ptr<Order> order) : order_(order) {}

    void execute() override {
        // Simulate order processing
        std::cout << "Processing order: " << order_->getId() << " - " << order_->getDetails() << std::endl;
    }

private:
    std::shared_ptr<Order> order_;
}; 
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <atomic>

class OrderQueue {
public:
    void enqueue(std::shared_ptr<Command> command) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(command);
        condition_.notify_one();
    }

    bool dequeue(std::shared_ptr<Command>& command) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty() || shutdown_; });

        if (!queue_.empty()) {
            command = queue_.front();
            queue_.pop();
            return true;
        }

        return false; // Shutdown and queue empty
    }

    void shutdown() {
        std::unique_lock<std::mutex> lock(mutex_);
        shutdown_ = true;
        condition_.notify_all();
    }

private:
    std::queue<std::shared_ptr<Command>> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool shutdown_ = false;
};
void orderConsumer(OrderQueue& orderQueue, std::atomic<int>& ordersProcessed) {
    while (true) {
        std::shared_ptr<Command> command;
        if (orderQueue.dequeue(command)) {
            command->execute();
            ordersProcessed++;
        }
        else {
            // Exit gracefully on shutdown
            break;
        }
    }
}
void orderProducer(OrderQueue& orderQueue, int orderCount) {
    for (int i = 0; i < orderCount; ++i) {
        auto order = std::make_shared<Order>("ORD" + std::to_string(i), "Order Details for order " + std::to_string(i));
        auto command = std::make_shared<ProcessOrderCommand>(order);
        orderQueue.enqueue(command);
    }
}
int main() {
    int numOrders = 100000; // Total orders to process
    OrderQueue orderQueue;
    std::atomic<int> ordersProcessed{ 0 };

    // Spawn consumer threads
    std::vector<std::thread> consumers;
    int numConsumers = std::thread::hardware_concurrency();
    for (int i = 0; i < numConsumers; ++i) {
        consumers.emplace_back(orderConsumer, std::ref(orderQueue), std::ref(ordersProcessed));
    }

    // Start producer
    orderProducer(orderQueue, numOrders);

    // Shutdown the queue once producer is done
    orderQueue.shutdown();

    // Join consumer threads
    for (auto& consumer : consumers) {
        consumer.join();
    }

    std::cout << "All orders processed: " << ordersProcessed << "/" << numOrders << std::endl;

    return 0;
}
