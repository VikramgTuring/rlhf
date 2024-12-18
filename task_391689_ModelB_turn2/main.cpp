#include <iostream>
#include <thread>
#include <future>
#include <queue>
#include <list>
#include <mutex>
#include <condition_variable>
#include <memory>

// Factory Pattern
class Order {
public:
    virtual void process() = 0;
    virtual ~Order() = default;
};

std::unique_ptr<Order> createOrder(const std::string& orderDetails) {
    // Simulate different types of orders, for simplicity, we'll just create one type here.
    return std::make_unique<SimpleOrder>(orderDetails);
}

class SimpleOrder : public Order {
public:
    SimpleOrder(const std::string& details) : details(details) {}

    void process() override {
        // Simulate processing
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::cout << "Processing order: " << details << std::endl;
    }

private:
    std::string details;
};

// Thread Pool
class ThreadPool {
public:
    ThreadPool(size_t numThreads) : workers(numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::unique_ptr<Runnable> task;
                    {
                        std::unique_lock<std::mutex> lock(taskQueueMutex);
                        taskQueueCondition.wait(lock, [this] {
                            return !taskQueue.empty() || stop;
                        });
                        if (stop) {
                            return;
                        }
                        task = std::move(taskQueue.front());
                        taskQueue.pop_front();
                    }
                    task->run();
                }
            });
        }
    }

    template<typename T>
    void enqueue(T&& f) {
        auto task = std::make_shared<Runnable>([f = std::move(f)]() { f(); });
        {
            std::unique_lock<std::mutex> lock(taskQueueMutex);
            taskQueue.push_back(std::move(task));
        }
        taskQueueCondition.notify_one();
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(taskQueueMutex);
            stop = true;
        }
        taskQueueCondition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

private:
    struct Runnable {
        virtual void run() = 0;
        virtual ~Runnable() = default;
    };

    template<typename Callable>
    class RunnableImpl : public Runnable {
    public:
        RunnableImpl(Callable&& callable) : callable(std::move(callable)) {}

        void run() override {
            callable();
        }

    private:
        Callable callable;
    };

    std::vector<std::thread> workers;
    std::queue<std::shared_ptr<Runnable>> taskQueue;
    std::mutex taskQueueMutex;
    std::condition_variable taskQueueCondition;
    bool stop = false;
};

// Observer Pattern for Order Status Update
class Observer {
public:
    virtual void update(const std::string& orderID, const std::string& status) = 0;
};

class OrderStatusObserver : public Observer {
public:
    void update(const std::string& orderID, const std::string& status) override {
        std::cout << "Order " << orderID << " status updated to: " << status << std::endl;
    }
};

class OrderManager {
public:
    OrderManager(ThreadPool& threadPool, std::list<Observer*>& observers)
        : threadPool(threadPool), observers(observers) {}

    void processOrder(const std::string& orderDetails) {
        std::unique_ptr<Order> order = createOrder(orderDetails);
        auto future = threadPool.enqueue([this, order = std::move(order)]() mutable {
            order->process();
            notifyObservers(order->details, "Processed");
        });
    }

private:
    void notifyObservers(const std::string& orderID, const std::string& status) {
        for (Observer* observer : observers) {
            observer->update(orderID, status);
        }
    }

    ThreadPool& threadPool;
    std::list<Observer*>& observers;
};
