#include <iostream>
#include <memory>

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

// Concrete implementation of a processing step
class BrightnessFilter : public ImageProcessor {
public:
    void processImage(Image& image) override {
        // Apply brightness adjustments
        std::cout << "Applying brightness filter." << std::endl;
        ImageProcessor::processImage(image); // Call next handler
    }
};

class ContrastFilter : public ImageProcessor {
public:
    void processImage(Image& image) override {
        // Apply contrast adjustments
        std::cout << "Applying contrast filter." << std::endl;
        ImageProcessor::processImage(image); // Call next handler
    }
};

class GrayscaleFilter : public ImageProcessor {
public:
    void processImage(Image& image) override {
        // Convert to grayscale
        std::cout << "Converting image to grayscale." << std::endl;
        ImageProcessor::processImage(image); // Call next handler
    }
};

// Example usage
int main() {
    // Create some image object
    Image image;

    // Create processing steps
    auto brightness = std::make_unique<BrightnessFilter>();
    auto contrast = std::make_unique<ContrastFilter>();
    auto grayscale = std::make_unique<GrayscaleFilter>();

    // Set up the chain of responsibility
    contrast->setNext(std::move(grayscale));      // Contrast -> Grayscale
    brightness->setNext(std::move(contrast));     // Brightness -> Contrast

    // Process the image through the chain
    brightness->processImage(image);

    // Display image at the end of processing
    image.display();

    return 0;
}

