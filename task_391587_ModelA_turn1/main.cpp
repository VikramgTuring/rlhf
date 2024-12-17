#include "Profiler.h"
#include "Singleton.h"
#include "Factory.h"
#include "Observer.h"

void benchmarkSingleton() {
    Profiler p("Single Operation of Singleton");
    Singleton::getInstance().operation();
}

void benchmarkFactory(int count) {
    Profiler p("Multiple Factory Creations");
    for (int i = 0; i < count; ++i) {
        auto product = Factory::createProduct("A");
        product->doSomething();
    }
}

void benchmarkObserver(int count) {
    Profiler p("Observer Notifications");
    Subject subject;
    std::vector<ConcreteObserverA> observers(count);

    for (auto& observer : observers) {
        subject.attach(&observer);
    }

    subject.notify();
}

int main() {
    // Running benchmarks
    benchmarkSingleton();
    benchmarkFactory(1000);  // Adjust the count for meaningful comparison
    benchmarkObserver(100);   // This could change depending on your needs

    return 0;
}
