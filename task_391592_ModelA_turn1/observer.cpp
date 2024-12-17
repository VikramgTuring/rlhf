#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// Observer Interface
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify() = 0;
};

// Subject Class
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify() = 0;
};

// Button Class acting as Subject
class Button : public ISubject {
public:
    void click() {
        std::cout << "Button clicked!" << std::endl;
        notify();
    }

    void attach(std::shared_ptr<IObserver> observer) override {
        observers.push_back(observer);
    }

    void detach(std::shared_ptr<IObserver> observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify() override {
        for (const auto& observer : observers) {
            observer->onNotify();
        }
    }

private:
    std::vector<std::shared_ptr<IObserver>> observers;
};

// Label Class acting as Observer
class Label : public IObserver {
public:
    void onNotify() override {
        std::cout << "Label updated because button clicked!" << std::endl;
    }
};

// Legacy-type usage example
int main() {
    Button button;
    
    // Using shared pointers for automatic memory management
    auto label = std::make_shared<Label>();
    
    button.attach(label);
    
    button.click();  // Would notify the Label

    return 0;
}
