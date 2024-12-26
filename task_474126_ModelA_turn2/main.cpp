#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define PAGE_SIZE 4096
#define LARGE_ALLOCATION_SIZE (10 * PAGE_SIZE)  // 10 pages

void allocate_large_memory() {
    // Attempt to allocate a large chunk of memory
    void *ptr = malloc(LARGE_ALLOCATION_SIZE);
    
    // Check if the allocation was successful
    if (ptr == NULL) {
        // Allocation failed, handle the error
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Use the allocated memory (initialize it, store data, etc.)
    memset(ptr, 'A', LARGE_ALLOCATION_SIZE);
    printf("Successfully allocated %d bytes of memory at %p\n", LARGE_ALLOCATION_SIZE, ptr);

    // Suppose we perform some operations here...

    // Free the allocated memory
    free(ptr);
}

int main() {
    allocate_large_memory();
    return 0;
}
