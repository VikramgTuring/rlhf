#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *data;
    size_t size;
    int ref_count;
    pthread_mutex_t mutex;   // Mutex for thread safety
} SharedArray;

// Function to initialize the mutex for a SharedArray
void init_mutex(SharedArray *arr) {
    pthread_mutex_init(&arr->mutex, NULL);
}

// Function to create a new SharedArray
SharedArray *create_shared_array(size_t size) {
    SharedArray *arr = (SharedArray *)malloc(sizeof(SharedArray));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed for SharedArray.\n");
        return NULL;
    }

    arr->data = (int *)malloc(size * sizeof(int));
    if (!arr->data) {
        fprintf(stderr, "Memory allocation failed for array data.\n");
        free(arr);
        return NULL;
    }

    arr->size = size;
    arr->ref_count = 1;
    init_mutex(arr);         // Initialize the mutex
    printf("SharedArray created with initial ref_count = %d.\n", arr->ref_count);
    return arr;
}

// Function to increase the reference count using a mutex
void retain_shared_array(SharedArray *arr) {
    if (arr) {
        pthread_mutex_lock(&arr->mutex);  // Acquire lock
        arr->ref_count++;
        pthread_mutex_unlock(&arr->mutex); // Release lock
        printf("SharedArray retained. New ref_count = %d.\n", arr->ref_count);
    }
}

// Function to decrease the reference count and free if needed using a mutex
void release_shared_array(SharedArray *arr) {
    if (arr) {
        pthread_mutex_lock(&arr->mutex);
        arr->ref_count--;

        printf("SharedArray released. New ref_count = %d.\n", arr->ref_count);
        // If no references remain, free memory
        if (arr->ref_count == 0) {
            printf("No references remaining. Freeing SharedArray.\n");
            free(arr->data);
            free(arr);
            pthread_mutex_destroy(&arr->mutex); // Destroy the mutex
        } else {
            pthread_mutex_unlock(&arr->mutex);
        }
    }
}

// Example simulation component using SharedArray
void simulate(SharedArray *arr) {
    printf("Simulating with SharedArray of size %zu.\n", arr->size);
    // Use shared array for simulation
    for (size_t i = 0; i < arr->size; i++) {
        arr->data[i] = i; // Simulate some data
        printf("arr->data[%zu] = %d\n", i, arr->data[i]);
    }
}

// Thread function that simulates work with a shared array
void *simulate_thread(void *arg) {
    SharedArray *shared_array = (SharedArray *)arg;

    // Simulate usage of the shared array
    retain_shared_array(shared_array);   // Retain array for this thread
    simulate(shared_array);

    release_shared_array(shared_array);  // Release array after simulation

    pthread_exit(NULL);
}

// Main function with multiple threads using the SharedArray
int main() {
    size_t array_size = 10;
    SharedArray *shared_array = create_shared_array(array_size);

    if (!shared_array) {
		printf("Failed to create shared array memory.\n");
        return EXIT_FAILURE;
    }

    const int num_threads = 4;
    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++) {
        printf("Creating thread %d.\n", i);
        pthread_create(&threads[i], NULL, simulate_thread, shared_array);
    }

    // Join all threads to wait for completion
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Program completed successfully.\n");
    return EXIT_SUCCESS;
}

