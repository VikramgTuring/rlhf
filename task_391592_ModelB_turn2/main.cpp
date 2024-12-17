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
	
    void removeSubscriber1() {

        subscriber1 = nullptr;

    }

private:

    Observer* subscriber1;

    Observer* subscriber2;

    void removeSubscriber1() {

        subscriber1 = nullptr;

    }
private:
    Subscriber1* subscriber1;
    Subscriber2* subscriber2;
};

int main() {
    EventSource eventSource;

    Subscriber1 subscriber1(eventSource);
    {

        Subscriber2 subscriber2(eventSource);  // Subscriber2 is in a block scope

    }  // Subscriber2 goes out of scope, but eventSource still holds its pointer
    
    eventSource.processEvent(); // Crash! Dangling pointer to Subscriber2 in                   eventSource::subscriber2


    return 0;
}
