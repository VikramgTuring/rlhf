#include <iostream>

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

class EventSource {
public:
    void processEvent() {
        std::cout << "Event generated." << std::endl;
        // Legacy code: Notify subscribers directly
        subscriber1->handleEvent();
        subscriber2->handleEvent();
    }

    void addSubscriber1(Subscriber1* subscriber) {
        subscriber1 = subscriber;
    }

    void addSubscriber2(Subscriber2* subscriber) {
        subscriber2 = subscriber;
    }

private:
    Subscriber1* subscriber1;
    Subscriber2* subscriber2;
};

int main() {
    EventSource eventSource;
    Subscriber1 subscriber1;
    Subscriber2 subscriber2;

    eventSource.addSubscriber1(&subscriber1);
    eventSource.addSubscriber2(&subscriber2);

    eventSource.processEvent();
    return 0;
}
