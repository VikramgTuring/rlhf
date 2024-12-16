#include <iostream>
#include <memory>
#include <vector>

// Image class remains the same

// Abstract handler for image processing
class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;

    void setNext(std::unique_ptr<ImageProcessor> next) {
        this->next = std::move(next);
    }

    void processImage(Image& image) {
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
    BrightnessFilter() = default;
    void processImage(Image& image) override {
        std::cout << "Applying brightness filter." << std::endl;
        processImage(image);
    }
};

class ContrastFilter : public ImageProcessor {
public:
    ContrastFilter() = default;
    void processImage(Image& image) override {
        std::cout << "Applying contrast filter." << std::endl;
        processImage(image);
    }
};

class GrayscaleFilter : public ImageProcessor {
public:
    GrayscaleFilter() = default;
    void processImage(Image& image) override {
        std::cout << "Converting image to grayscale." << std::endl;
        processImage(image);
    }
};

// Helper function to build the chain dynamically
std::unique_ptr<ImageProcessor> createImageProcessingChain(const std::vector<std::unique_ptr<ImageProcessor>>& steps) {
    std::unique_ptr<ImageProcessor> current;
    for (auto& step : steps) {
        if (!current) {
            current = std::move(step);
        } else {
            current->setNext(std::move(step));
        }
    }
    return current;
}

// Example usage
int main() {
    Image image;

    // Define processing steps
    std::vector<std::unique_ptr<ImageProcessor>> processors = {
        std::make_unique<BrightnessFilter>(),
        std::make_unique<ContrastFilter>(),
        std::make_unique<GrayscaleFilter>(),
    };

    // Build the chain using the helper function
    auto processingChain = createImageProcessingChain(processors);

    // Process the image through the chain
    if (processingChain) {
        processingChain->processImage(image);
    }

    image.display();

    return 0;
}
