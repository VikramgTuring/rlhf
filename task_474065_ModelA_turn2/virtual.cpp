#include <iostream>
#include <cstdlib>      // For malloc and free
#include <cstring>      // For memset
#include <unistd.h>     // For sysconf (to get page size)
#include <cstdint>      // For uintptr_t

void analyzeMemory(size_t size) {
    std::cout << "Requesting allocation of " << size << " bytes.\n";

    // Allocate memory
    void* ptr = malloc(size);
    if (!ptr) {
        std::cerr << "malloc failed to allocate memory.\n";
        return;
    }

    // Obtain page size
    size_t pageSize = sysconf(_SC_PAGESIZE);

    // Determine page boundaries
    uintptr_t startAddr = reinterpret_cast<uintptr_t>(ptr);
    uintptr_t endAddr = startAddr + size - 1;
    uintptr_t startPage = startAddr / pageSize;
    uintptr_t endPage = endAddr / pageSize;

    std::cout << "Memory allocation starts at address: 0x" << std::hex << startAddr << std::dec << "\n";
    std::cout << "Memory allocation ends at address: 0x" << std::hex << endAddr << std::dec << "\n";
    std::cout << "Page size: " << pageSize << " bytes\n";
    std::cout << "Memory spans " << (endPage - startPage + 1) << " page(s).\n";

    // Access the memory to ensure it triggers page faults
    memset(ptr, 0, size);

    // Free the memory
    free(ptr);
    std::cout << "Memory freed.\n\n";
}

int main() {
    // Allocate memory smaller than a page
    analyzeMemory(1024); // 1 KB

    // Allocate memory crossing a page boundary
    analyzeMemory(8192 + 1024); // 9 KB (crosses 2 pages)

    // Allocate a large block spanning multiple pages
    analyzeMemory(32768); // 32 KB (crosses 8 pages)

    return 0;
}

