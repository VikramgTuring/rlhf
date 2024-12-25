#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    int ref_count;   // Reference count
} SharedArray;

// Function to create a new SharedArray
SharedArray *create_shared_array(size_t size) {
    printf("Creating a new SharedArray of size %zu.\n", size);
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
    printf("SharedArray created with initial ref_count = %d.\n", arr->ref_count);
    return arr;
}

// Function to increase the reference count
void retain_shared_array(SharedArray *arr) {
    if (arr) {
        arr->ref_count++;
        printf("SharedArray retained. New ref_count = %d.\n", arr->ref_count);
    }
}

// Function to decrease the reference count and free if needed
void release_shared_array(SharedArray *arr) {
    if (arr) {
        arr->ref_count--;
        printf("SharedArray released. New ref_count = %d.\n", arr->ref_count);
        // If no references remain, free memory
        if (arr->ref_count == 0) {
            printf("No references remaining. Freeing SharedArray.\n");
            free(arr->data);
            free(arr);
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

int main() {
    size_t array_size = 10;

    // Create a new shared array
    SharedArray *shared_array = create_shared_array(array_size);
    if (!shared_array) {
		 printf("Failed to create shared array memory.\n");
        return EXIT_FAILURE; // Handle allocation error
    }

    // Simulate using the shared array
    simulate(shared_array);
    
    // Example of retaining the array reference
    printf("Retaining the SharedArray reference.\n");
    retain_shared_array(shared_array);

    // Do something else...

    // Release shared array references
    printf("Releasing the SharedArray references.\n");
    release_shared_array(shared_array);
    release_shared_array(shared_array); // This will free the memory

    printf("Program completed successfully.\n");
    return EXIT_SUCCESS;
}

