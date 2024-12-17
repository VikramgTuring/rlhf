#include <atomic>
#include <queue>
#include <thread>

class ThreadPool {
public:
    ThreadPool(int numThreads) : workers(numThreads) {
        for (int i = 0; i < numThreads; ++i) {
            workers[i] = std::thread([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        queueCondition.wait(lock, [this] {
                            return stop || !taskQueue.empty();
                        });
                        if (stop && taskQueue.empty()) {
                            return;
                        }
                        task = std::move(taskQueue.front());
                        taskQueue.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        queueCondition.notify_all();
        for (auto& worker : workers) {
            worker.join();
        }
    }

    template <typename Task>
    void enqueue(Task&& task) {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.emplace_back(std::forward<Task>(task));
        queueCondition.notify_one();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
    bool stop = false;
};

class Subject {
public:
    Subject(ThreadPool& threadPool) : threadPool(threadPool) {}

    void registerObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        for (auto observer : observers) {
            threadPool.enqueue([observer] { observer->update(); });
        }
    }

    void doWork() {
        // Simulate work that notifies observers
        for (int i = 0; i < 10000000; ++i) {
        }
        notifyObservers();
    }

private:
    vector<Observer*> observers;
    ThreadPool& threadPool;
};

int main() {
    ThreadPool threadPool(4); // Use a fixed number of worker threads

    {
        cout << "Profiling Observer with asynchronous notifications..." << endl;
        Subject subject(threadPool);
        ConcreteObserver observer(&subject);
        auto time = measureTime([&] {
            subject.doWork();
        });
        cout << "Execution time: " << time << " ms" << endl;
    }

    return 0;
}
