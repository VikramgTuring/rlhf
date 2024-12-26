#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LARGE_ALLOC_SIZE (1024 * 1024 * 100) // 100 MB allocation

int large_memory_allocation() {
    void *ptr = malloc(LARGE_ALLOC_SIZE);

    if (ptr == NULL) {
        perror("malloc failed");
        fprintf(stderr, "Error code: %d\n", errno);
        switch (errno) {
            case ENOMEM:
                fprintf(stderr, "Not enough memory available.\n");
                break;
            default:
                break;
        }
        return 1;
    }

    printf("Large memory allocation successful: %p\n", ptr);

    free(ptr);
    return 0;
}

int main() {
    if (large_memory_allocation() != 0) {
        fprintf(stderr, "Large memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("Large memory allocation example completed.\n");
    return 0;
}
