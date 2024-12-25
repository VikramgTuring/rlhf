#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Define a "smart pointer" struct in the spirit of RAII
typedef struct data_holder_t {
    void *data; // Pointer to the dynamically allocated memory
    int size; // Size of the allocated memory
} data_holder_t;

void* thread_func(void *arg) {
    data_holder_t* input_data = (data_holder_t*) arg;
    printf("Thread: Operating on data of size %d\n", input_data->size);
    
    // Perform operations on the data
    free_data_holder(input_data);
    return NULL;
}

data_holder_t *allocate_data(int size) {
    data_holder_t *holder = malloc(sizeof(data_holder_t));
    if (!holder) {
        fprintf(stderr, "Failed to allocate memory for data holder.\n");
        return NULL;
    }

    holder->data = malloc(size);
    if (!holder->data) {
        free(holder);
        fprintf(stderr, "Failed to allocate dynamic memory.\n");
        return NULL;
    }

    holder->size = size;
    return holder;
}

void free_data_holder(data_holder_t *holder) {
    if (holder->data) {
        free(holder->data);
    }
    free(holder);
}

int main() {
    const int num_threads = 4;
    data_holder_t *shared_data = allocate_data(1024); // 1KB of data for example

    if (!shared_data) {
        exit(EXIT_FAILURE);
    }

    // Example of synchronized access using a mutex (This is not included here)

    /* exemple pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);*/

    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, shared_data)) {
            perror("thread creation failed");
            free_data_holder(shared_data);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Main: Program finished, all threads completed.\n");
