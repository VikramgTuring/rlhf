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

// Adapter class: Implements the old Button::Label interface while using the Observer Pattern
class ButtonLegacyAdapter : public Button::Label {
public:
    ButtonLegacyAdapter(Button& button) : button(button) {}

    void onButtonClicked() override {
        // When onButtonClicked is called, notify observers through the new Button class
        button.notify();
    }

private:
    Button& button;
};

int main() {
    Button button;

    // Using the adapter to bridge the old interface
    ButtonLegacyAdapter adapter(button);

    // Using shared pointers for automatic memory management
    auto label = std::make_shared<Label>();
    button.attach(label);

    // Legacy code uses the adapter
    adapter.onButtonClicked();

    return 0;
}
