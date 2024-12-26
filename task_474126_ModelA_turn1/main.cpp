#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PAGE_SIZE 4096

void allocate_memory() {
    // Let's allocate a large amount of memory that likely exceeds a single page
    size_t total_size = 3 * PAGE_SIZE; // 3 pages worth of memory
    void *ptr = malloc(total_size);

    if (ptr == NULL) {
        perror("malloc failed");
        return;
    }

    // Fill the memory with data
    memset(ptr, 'A', total_size);

    // Print the starting and ending addresses
    printf("Allocated memory from %p to %p\n", ptr, (char *)ptr + total_size);

    // Simulate memory access across pages
    printf("First byte: %c\n", *((char *)ptr)); // Should print 'A'
    printf("Last byte: %c\n", *((char *)ptr + total_size - 1)); // Should also print 'A'

    // Free the allocated memory
    free(ptr);
}

int main() {
    allocate_memory();
    return 0;
}
