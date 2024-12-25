#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
    int ref_count;
} SharedArray;

pthread_mutex_t memory_lock; // Mutex for thread-safe memory management

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
    arr->ref_count = 1; // Initial reference count
    return arr;
}

// Function to increase the reference count
void retain_shared_array(SharedArray *arr) {
    if (arr) {
        arr->ref_count++;
    }
}

// Function to decrease the reference count and free if needed
void release_shared_array(SharedArray *arr) {
    if (arr) {
        arr->ref_count--;
        if (arr->ref_count == 0) {
            free(arr->data);
            free(arr);
        }
    }
}

// Thread function to simulate memory operations
void *thread_function(void *arg) {
    size_t size = *(size_t *)arg;

    // Lock the memory allocation section
    pthread_mutex_lock(&memory_lock);
    
    // Create a shared array
    SharedArray *shared_array = create_shared_array(size);
    if (shared_array) {
        // Simulate some operations on the shared array
        for (size_t i = 0; i < shared_array->size; i++) {
            shared_array->data[i] = i; // Populate data
        }

        // Retain and release the shared array
        retain_shared_array(shared_array);
        release_shared_array(shared_array);
    }

    pthread_mutex_unlock(&memory_lock);
    return NULL;
}

int main() {
    pthread_t threads[5];
    size_t array_size = 10;

    // Initialize the mutex
    pthread_mutex_init(&memory_lock, NULL);

    // Create multiple threads
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, &array_size) != 0) {
            fprintf(stderr, "Error creating thread.\n");
            return EXIT_FAILURE;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up mutex
    pthread_mutex_destroy(&memory_lock);
    printf("Program completed successfully.\n");
    return EXIT_SUCCESS;
}
