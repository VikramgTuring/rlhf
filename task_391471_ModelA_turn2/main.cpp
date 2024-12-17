#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>

// Image class representing an image object
class Image {
public:
    void display() { std::cout << "Displaying image." << std::endl; }
    // Additional properties and methods can be added (e.g. pixels, size)
};

// Abstract handler for image processing
class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;

    void setNext(std::unique_ptr<ImageProcessor> next) {
        this->next = std::move(next);
    }

    virtual void processImage(Image& image) {
        if (next) {
            next->processImage(image);
        }
    }

protected:
    std::unique_ptr<ImageProcessor> next;
};

// Concrete implementations of processing steps
class BrightnessFilter : public ImageProcessor {
public:
    void processImage(Image& image) override {
        std::cout << "Applying brightness filter." << std::endl;
        ImageProcessor::processImage(image);
    }
};

class ContrastFilter : public ImageProcessor {
public:
    void processImage(Image& image) override {
        std::cout << "Applying contrast filter." << std::endl;
        ImageProcessor::processImage(image);
    }
};

class GrayscaleFilter : public ImageProcessor {
public:
    void processImage(Image& image) override {
        std::cout << "Converting image to grayscale." << std::endl;
        ImageProcessor::processImage(image);
    }
};

// Thread Pool Class
class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    
    template<class F>
    auto enqueue(F&& f) -> std::future<typename std::result_of<F()>::type>;

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

// Implementation of the Thread Pool
ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queueMutex);
                    this->condition.wait(lock, [this] {
                        return this->stop || !this->tasks.empty();
                    });
                    if (this->stop && this->tasks.empty()) 
                        return;
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker: workers) {
        worker.join();
    }
}

template<class F>
auto ThreadPool::enqueue(F&& f) -> std::future<typename std::result_of<F()>::type> {
    using return_type = typename std::result_of<F()>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));
    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}

// Example usage
int main() {
    const size_t numImages = 10;
    const size_t numThreads = 4;

    // Create some dummy images
    std::vector<Image> images(numImages);

    // Create processing steps
    auto brightness = std::make_unique<BrightnessFilter>();
    auto contrast = std::make_unique<ContrastFilter>();
    auto grayscale = std::make_unique<GrayscaleFilter>();

    // Set up the chain of responsibility
    contrast->setNext(std::move(grayscale));
    brightness->setNext(std::move(contrast));

    // Create a thread pool
    ThreadPool pool(numThreads);

    // Vector to hold future results
    std::vector<std::future<void>> results;

    for (auto& image : images) {
        // Enqueue the image processing task
        results.emplace_back(pool.enqueue([&image, &brightness]() {
            brightness->processImage(image);
            image.display();  // Can be called after processing
        }));
    }

    // Waiting for all tasks to finish
    for (auto && result : results) {
        result.get();
    }

    return 0;
}
