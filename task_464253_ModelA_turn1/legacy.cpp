#include <cstdio>
#include <thread>
#include <chrono>

void performComputation(int id) {
    for (int i = 0; i < 10; ++i) {
        // Simulate computation
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        printf("Thread %d: Iteration %d\n", id, i);
    }
}

int main() {
    std::thread t1(performComputation, 1);
    std::thread t2(performComputation, 2);

    t1.join();
    t2.join();

    return 0;
}
