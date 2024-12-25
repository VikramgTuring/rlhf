#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    int ref_count;   // Reference count
} SharedArray;

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
        // If no references remain, free memory
        if (arr->ref_count == 0) {
            free(arr->data);
            free(arr);
        }
    }
}

// Example simulation component using SharedArray
void simulate(SharedArray *arr) {
    // Use shared array for simulation
    for (size_t i = 0; i < arr->size; i++) {
        arr->data[i] = i; // Simulate some data
    }
}

int main() {
    size_t array_size = 10;

    // Create a new shared array
    SharedArray *shared_array = create_shared_array(array_size);
    if (!shared_array) {
        return EXIT_FAILURE; // Handle allocation error
    }

    // Simulate using the shared array
    simulate(shared_array);
    
    // Example of retaining the array reference
    retain_shared_array(shared_array);

    // Do something else...

    // Release shared array references
    release_shared_array(shared_array);
    release_shared_array(shared_array); // This will free the memory

    return EXIT_SUCCESS;
}
