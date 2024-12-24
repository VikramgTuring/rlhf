#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <ctime>

struct CacheEntry {
    std::string ipAddress;
    time_t expiryTime; // Stores the time when the entry should expire
};

class DnsCache {
public:
    void add(const std::string& domain, const std::string& ipAddress, int ttl) {
        time_t currentTime = time(nullptr);
        CacheEntry entry = { ipAddress, currentTime + ttl };
        cache[domain] = entry;
        printf("[CACHE ADD] Domain: %s, IP: %s, TTL: %d seconds\n", domain.c_str(), ipAddress.c_str(), ttl);
    }

    std::string resolve(const std::string& domain) {
        time_t currentTime = time(nullptr);
        
        auto it = cache.find(domain);
        if (it != cache.end()) {
            CacheEntry& entry = it->second;

            // Check if the cache entry has expired
            if (currentTime < entry.expiryTime) {
                printf("[CACHE HIT] Domain: %s, IP: %s, TTL Remaining: %ld seconds\n", 
                       domain.c_str(), entry.ipAddress.c_str(), 
                       entry.expiryTime - currentTime);
                return entry.ipAddress; // Cache hit
            } else {
                printf("[CACHE MISS] Domain: %s has expired. Expired at %s\n", 
                       domain.c_str(), ctime(&entry.expiryTime));
                cache.erase(it); // Remove expired entry
            }
        }
        
        printf("[CACHE MISS] Domain: %s not found in cache.\n", domain.c_str());
        return ""; // Cache miss
    }

    void printCache() const {
        printf("[CACHE STATUS]\n");
        for (const auto& entry : cache) {
            printf("Domain: %s, IP: %s, Expires at: %s", 
                   entry.first.c_str(), entry.second.ipAddress.c_str(), 
                   ctime(&entry.second.expiryTime));
        }
    }

private:
    std::unordered_map<std::string, CacheEntry> cache;
};

int main() {
    DnsCache dnsCache;

    // Add entries to the cache
    dnsCache.add("example.com", "93.184.216.34", 10); // TTL of 10 seconds
    dnsCache.add("openai.com", "104.18.25.178", 5);  // TTL of 5 seconds

    // Wait for a while and resolve domains
    std::this_thread::sleep_for(std::chrono::seconds(3));
    dnsCache.resolve("example.com"); // Should be a hit
    dnsCache.resolve("openai.com");   // Should be a hit

    std::this_thread::sleep_for(std::chrono::seconds(4)); // Total wait 7s
    dnsCache.resolve("example.com"); // Should be a hit
    dnsCache.resolve("openai.com");   // Should be a miss now

    std::this_thread::sleep_for(std::chrono::seconds(5)); // Total wait 12s
    dnsCache.printCache(); // Check cache status

    return 0;
}
