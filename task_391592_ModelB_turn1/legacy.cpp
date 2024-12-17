#include <iostream>

class EventSource {
public:
    void processEvent() {
        std::cout << "Event generated." << std::endl;
        // Legacy code: Notify subscribers directly
        subscriber1->handleEvent();
        subscriber2->handleEvent();
    }

    void addSubscriber(void* subscriber) {
        subscribers.push_back(subscriber);
    }

private:
    std::vector<void*> subscribers;
};

class Subscriber1 {
public:
    void handleEvent() {
        std::cout << "Subscriber1: Event received." << std::endl;
    }
};

class Subscriber2 {
public:
    void handleEvent() {
        std::cout << "Subscriber2: Event received." << std::endl;
    }
};

int main() {
    EventSource eventSource;
    Subscriber1 subscriber1;
    Subscriber2 subscriber2;

    eventSource.addSubscriber(&subscriber1);
    eventSource.addSubscriber(&subscriber2);

    eventSource.processEvent();
    return 0;
}
