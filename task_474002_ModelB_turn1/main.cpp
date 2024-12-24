#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // For gettimeofday (on Unix-like systems)

#define MAX_CACHE_SIZE 10
#define CACHE_ENTRY_TTL 3600 // TTL in seconds (example: 1 hour)

struct cache_entry {
    char domain[256];
    time_t expiration_time;
    int data; // Example: You can store IP address or any relevant data here
};

cache_entry dns_cache[MAX_CACHE_SIZE];

int cache_get(char* domain) {
    for (int i = 0; i < MAX_CACHE_SIZE; i++) {
        struct timeval now;
        gettimeofday(&now, NULL);
        time_t current_time = (time_t)now.tv_sec;

        if (strcmp(dns_cache[i].domain, domain) == 0 &&
            dns_cache[i].expiration_time > current_time) {

            // Cache hit
            printf("Cache hit: Domain '%s' found in cache (Expires: %s)\n",
                    dns_cache[i].domain,
                    ctime(&dns_cache[i].expiration_time));
            return dns_cache[i].data;
        }
    }

    // Cache miss
    printf("Cache miss: Domain '%s' not found in cache.\n", domain);
    return -1;
}

void cache_set(char* domain, int data) {
    struct timeval now;
    gettimeofday(&now, NULL);
    time_t current_time = (time_t)now.tv_sec;
    time_t expiration_time = current_time + CACHE_ENTRY_TTL;

    for (int i = 0; i < MAX_CACHE_SIZE; i++) {
        if (dns_cache[i].domain[0] == '\0') {
            // Empty slot found, insert here
            strcpy(dns_cache[i].domain, domain);
            dns_cache[i].expiration_time = expiration_time;
            dns_cache[i].data = data;
            printf("Domain '%s' added to cache (Expires: %s)\n",
                    dns_cache[i].domain,
                    ctime(&dns_cache[i].expiration_time));
            return;
        }
    }

    // Cache full, remove the oldest entry
    int oldest_index = 0;
    for (int i = 1; i < MAX_CACHE_SIZE; i++) {
        if (dns_cache[i].expiration_time < dns_cache[oldest_index].expiration_time) {
            oldest_index = i;
        }
    }

    // Replace the oldest entry
    strcpy(dns_cache[oldest_index].domain, domain);
    dns_cache[oldest_index].expiration_time = expiration_time;
    dns_cache[oldest_index].data = data;
    printf("Cache full: Domain '%s' evicted to make space for '%s' (Expires: %s)\n",
            dns_cache[oldest_index].domain, domain,
            ctime(&dns_cache[oldest_index].expiration_time));
}

int main() {
    cache_set("example.com", 192.168.1.1);
    cache_set("www.example.com", 192.168.1.2);
    cache_set("google.com", 8.8.8.8);

    printf("Cached entries:\n");
    for (int i = 0; i < MAX_CACHE_SIZE; i++) {
        if (dns_cache[i].domain[0] != '\0') {
            printf("%s: %d\n", dns_cache[i].domain, dns_cache[i].data);
        }
    }
