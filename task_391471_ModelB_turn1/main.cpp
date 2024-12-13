class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;
    virtual void processImage(cv::Mat& image) = 0;
    virtual ImageProcessor* getNextProcessor() const = 0;
    virtual void setNextProcessor(ImageProcessor* next) = 0;
};

class FilterProcessor : public ImageProcessor {
public:
    FilterProcessor(ImageProcessor* next = nullptr) : nextProcessor(next) {}
    ~FilterProcessor() override { delete nextProcessor; }

    void processImage(cv::Mat& image) override {
        // Apply filtering to the image
        cv::GaussianBlur(image, image, cv::Size(5, 5), 0, 0);
        if (nextProcessor) {
            nextProcessor->processImage(image);
        }
    }

    ImageProcessor* getNextProcessor() const override {
        return nextProcessor;
    }

    void setNextProcessor(ImageProcessor* next) override {
        nextProcessor = next;
    }

private:
    ImageProcessor* nextProcessor;
};

class ResizeProcessor : public ImageProcessor {
public:
    ResizeProcessor(const cv::Size& targetSize, ImageProcessor* next = nullptr) : targetSize(targetSize), nextProcessor(next) {}
    ~ResizeProcessor() override { delete nextProcessor; }

    void processImage(cv::Mat& image) override {
        // Apply resizing to the image
        cv::resize(image, image, targetSize, 0, 0, cv::INTER_AREA);
        if (nextProcessor) {
            nextProcessor->processImage(image);
        }
    }

    ImageProcessor* getNextProcessor() const override {
        return nextProcessor;
    }

    void setNextProcessor(ImageProcessor* next) override {
        nextProcessor = next;
    }

private:
    cv::Size targetSize;
    ImageProcessor* nextProcessor;
};

int main() {
    cv::Mat inputImage = cv::imread("input.jpg");

    // Create processors
    ImageProcessor* filterProcessor = new FilterProcessor();
    ImageProcessor* resizeProcessor = new ResizeProcessor(cv::Size(640, 480));

    // Chain the processors
    filterProcessor->setNextProcessor(resizeProcessor);

    // Process the image through the chain
    filterProcessor->processImage(inputImage);

    // Display the processed image
    cv::imshow("Processed Image", inputImage);
    cv::waitKey(0);

    // Clean up
    delete resizeProcessor;
    delete filterProcessor;

    return 0;
}
