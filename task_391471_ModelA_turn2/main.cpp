#include <iostream>
#include <memory>
#include <vector>

// Image class representing an image object
class Image {
public:
    void display() { std::cout << "Displaying image." << std::endl; }

    // Additional properties and methods can be added (e.g., pixels, size)
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

// Function to build a processing chain from a list of processors
std::unique_ptr<ImageProcessor> buildProcessingChain(std::vector<std::unique_ptr<ImageProcessor>>& processors) {
    if (processors.empty()) return nullptr;

    for (size_t i = 0; i < processors.size() - 1; ++i) {
        processors[i]->setNext(std::move(processors[i + 1]));
    }

    return std::move(processors[0]); // return the first processor
}

// Example usage
int main() {
    // Create some image object
    Image image;

    // Create processing steps
    std::vector<std::unique_ptr<ImageProcessor>> processors;
    processors.push_back(std::make_unique<BrightnessFilter>());
    processors.push_back(std::make_unique<ContrastFilter>());
    processors.push_back(std::make_unique<GrayscaleFilter>());

    // Build the processing chain
    auto processingChain = buildProcessingChain(processors);

    // Process the image through the chain
    if (processingChain) {
        processingChain->processImage(image);
    }

    // Display image at the end of processing
    image.display();

    return 0;
}
