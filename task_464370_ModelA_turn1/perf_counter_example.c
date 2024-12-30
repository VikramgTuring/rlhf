#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PERF_EVENT_FD_CLOEXEC 0x80000000
#define PERF_EVENT_ATTR_SAMPLE_PERIOD 7

#define NUM_ITERATIONS 10000000

uint64_t read_counter(int fd) {
    struct perf_event_mmap_page p;
    read(fd, &p, sizeof(p));
    return p.perf_counter.value;
}

int open_perf_counter(uint32_t config) {
    int fd = syscall(__NR_perf_event_open,
                     &(struct perf_event_attr){
                         .type = PERF_TYPE_HARDWARE,
                         .size = sizeof(struct perf_event_attr),
                         .config = config,
                         .disabled = 1,
                         .exclude_kernel = 1,
                         .exclude_hv = 1,
                     },
                     -1, -1, -1, PERF_EVENT_FD_CLOEXEC);

    if (fd == -1) {
        perror("perf_event_open");
        exit(EXIT_FAILURE);
    }

    return fd;
}

void darting_pattern(int x) {
    for (int i = 0; i < 10; i++) {
        int y = i * x + 3;
        for (int j = 0; j < y; j++) {
            volatile int z = j * j;
        }
    }
}

int main() {
    uint32_t config = PERF_COUNT_EVENT_INSTRUCTIONS;
    int perf_fd = open_perf_counter(config);

    // Ensure the counter is stopped before starting
    syscall(__NR_perf_event_open, NULL, perf_fd, -1, -1, 0);

    uint64_t start, end;

    // Measure with inline function
    printf("Measuring with inline function...\n");
    __attribute__((always_inline))
    void darting_pattern_inline(int x) {
        for (int i = 0; i < 10; i++) {
            int y = i * x + 3;
            for (int j = 0; j < y; j++) {
                volatile int z = j * j;
            }
        }
    }

    start = read_counter(perf_fd);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        darting_pattern_inline(i);
    }
    end = read_counter(perf_fd);
    uint64_t instructions_inlined = end - start;

    printf("Instruction count with inline: %lu\n", instructions_inlined);

    // Measure without inline function
    printf("\nMeasuring without inline function...\n");
    start = read_counter(perf_fd);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        darting_pattern(i);
    }
    end = read_counter(perf_fd);
    uint64_t instructions_not_inlined = end - start;

    printf("Instruction count without inline: %lu\n", instructions_not_inlined);

    close(perf_fd);

    return 0;
}
