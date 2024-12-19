#include <iostream>
#include <thread>
#include <chrono>

void compute(int thread_id) {
    for (int i = 0; i < 5; ++i) {
        // Simulate computation work
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        printf("Thread %d: Computing iteration %d\n", thread_id, i);
        
        if (i == 2) {
            printf("Thread %d: Halfway there!\n", thread_id);
        }
    }
    printf("Thread %d: Finished computation.\n", thread_id);
}

int main() {
    std::thread t1(compute, 1);
    std::thread t2(compute, 2);

    t1.join();
    t2.join();

    return 0;
}
