#include <iostream>
#include <memory>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

// Image class representing an image object
class Image {
public:
    void display() { std::cout << "Displaying image." << std::endl; }
};

// Abstract handler for image processing
class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;

    // Set the next handler in the chain
    void setNext(std::unique_ptr<ImageProcessor> next) {
        this->next = std::move(next);
    }

    // Process the image and forward to the next handler
    virtual void processImage(Image& image) {
        if (next) {
            next->processImage(image);
        }
    }

protected:
    std::unique_ptr<ImageProcessor> next;
};

// Concrete implementation of processing steps
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

// Thread-safe queue for processing tasks
class TaskQueue {
public:
    void enqueue(std::unique_ptr<Image> image) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(image));
        condition.notify_one();
    }

    std::unique_ptr<Image> dequeue() {
        std::unique_ptr<Image> image;
        {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this] { return !queue.empty(); });
            image = std::move(queue.front());
            queue.pop();
        }
        return image;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

private:
    std::mutex mutex;
    std::condition_variable condition;
    std::queue<std::unique_ptr<Image>> queue;
};

// Worker thread function
void workerThread(TaskQueue& taskQueue, std::unique_ptr<ImageProcessor> head) {
    while (!taskQueue.empty() || true) {
        std::unique_ptr<Image> image = taskQueue.dequeue();
        if (image) {
            head->processImage(*image);
            image->display();
        }
    }
}

// Example usage with multithreading
int main() {
    TaskQueue taskQueue;

    // Create some image objects
    for (int i = 0; i < 10; ++i) {
        auto image = std::make_unique<Image>();
        taskQueue.enqueue(std::move(image));
    }

    // Create processing steps
    auto brightness = std::make_unique<BrightnessFilter>();
    auto contrast = std::make_unique<ContrastFilter>();
    auto grayscale = std::make_unique<GrayscaleFilter>();

    // Set up the chain of responsibility
    contrast->setNext(std::move(grayscale));
    brightness->setNext(std::move(contrast));

    // Start worker threads
    const int numThreads = 4;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(workerThread, std::ref(taskQueue), std::move(brightness));
    }

    // Wait for all images to be processed
    while (!taskQueue.empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Join worker threads
    for (std::thread& thread : threads) {
        thread.join();
    }

    return 0;
}
