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

    std::shared_ptr<Command> dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty(); });

        auto command = queue_.front();
        queue_.pop();
        return command;
    }

private:
    std::queue<std::shared_ptr<Command>> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
};
void orderConsumer(OrderQueue& orderQueue) {
    while (true) {
        auto command = orderQueue.dequeue();
        command->execute();
    }
}
void orderProducer(OrderQueue& orderQueue, int orderCount) {
    for (int i = 0; i < orderCount; ++i) {
        auto order = std::make_shared<Order>("ORD" + std::to_string(i), "Order Details for order " + std::to_string(i));
        auto command = std::make_shared<ProcessOrderCommand>(order);
        orderQueue.enqueue(command);
    }
}
int main()
{
    int numOrders = 100; // Total orders to process
    OrderQueue orderQueue;

    // Spawn consumer threads
    std::vector<std::thread> consumers;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) { // Use available hardware threads
        consumers.emplace_back(orderConsumer, std::ref(orderQueue));
    }

    // Order producer
    orderProducer(orderQueue, numOrders);

    // Join consumer threads (you might want to implement a graceful shutdown)
    for (auto& consumer : consumers) {
        consumer.detach(); // Detach for simplicity
    }

    return 0;
}
