#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For getpagesize
#include <sys/mman.h>  // For mmap, munmap, msync

// Function to demonstrate memory allocation crossing page boundaries
int main() {
    size_t page_size = getpagesize();
    printf("Page size: %zu bytes\n", page_size);

    // Allocate a block of memory that is slightly larger than a page to potentially span boundaries
    void* ptr = malloc(page_size * 2);
    if (ptr == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // Print the addresses to see if they span page boundaries
    printf("Allocated address: %p\n", ptr);
    printf("Address after page_size bytes: %p\n", (char*)ptr + page_size);

    // Let's modify a byte at the start and end of the allocated block
    *(char*)ptr = 'A';
    *(char*)ptr + page_size - 1 = 'B';

    free(ptr);

    return 0;
}
