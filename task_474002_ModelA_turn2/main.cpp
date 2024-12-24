#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>

enum LogLevel {
    ERROR,
    WARN,
    INFO
};

class Logger {
public:
    Logger(LogLevel level) : logLevel(level) {}

    void log(LogLevel level, const char* format, ...) {
        if (level <= logLevel) {
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            va_end(args);
        }
    }

private:
    LogLevel logLevel;
};

struct CacheEntry {
    std::string ipAddress;
    time_t expiryTime; // Stores the time when the entry should expire
};

class DnsCache {
public:
    DnsCache(Logger& logger) : logger(logger), totalQueries(0), cacheHits(0), cacheMisses(0) {}

    void add(const std::string& domain, const std::string& ipAddress, int ttl) {
        time_t currentTime = time(nullptr);
        CacheEntry entry = { ipAddress, currentTime + ttl };
        cache[domain] = entry;
        logger.log(INFO, "[CACHE ADD] Domain: %s, IP: %s, TTL: %d seconds\n", domain.c_str(), ipAddress.c_str(), ttl);
    }

    std::string resolve(const std::string& domain) {
        totalQueries++;
        time_t currentTime = time(nullptr);
        
        auto it = cache.find(domain);
        if (it != cache.end()) {
            CacheEntry& entry = it->second;

            // Check if the cache entry has expired
            if (currentTime < entry.expiryTime) {
                cacheHits++;
                logger.log(INFO, "[CACHE HIT] Domain: %s, IP: %s, TTL Remaining: %ld seconds\n", 
                           domain.c_str(), entry.ipAddress.c_str(), 
                           entry.expiryTime - currentTime);
                return entry.ipAddress; // Cache hit
            } else {
                logger.log(WARN, "[CACHE MISS] Domain: %s has expired. Expired at %s\n", 
                           domain.c_str(), ctime(&entry.expiryTime));
                cache.erase(it); // Remove expired entry
            }
        }
        
        cacheMisses++;
        logger.log(INFO, "[CACHE MISS] Domain: %s not found in cache.\n", domain.c_str());
        return ""; // Cache miss
    }

    void printCacheSummary() const {
        logger.log(INFO, "[CACHE SUMMARY] Total Queries: %d, Cache Hits: %d, Cache Misses: %d\n", 
                   totalQueries, cacheHits, cacheMisses);
    }

private:
    std::unordered_map<std::string, CacheEntry> cache;
    Logger& logger;
    int totalQueries;
    int cacheHits;
    int cacheMisses;
};

int main() {
    Logger logger(INFO); // Set log level to INFO
    DnsCache dnsCache(logger);

    // Add entries to the cache
    dnsCache.add("example.com", "93.184.216.34", 10); // TTL of 10 seconds
    dnsCache.add("openai.com", "104.18.25.178", 5);  // TTL of 5 seconds

    // Simulate DNS resolution
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        dnsCache.resolve("example.com"); // Should hit until expiration
        dnsCache.resolve("openai.com");   // Should hit until expiration
        dnsCache.resolve("nonexistent.com"); // Should always miss
    }

    dnsCache.printCacheSummary(); // Print summary of cache usage

    return 0;
}
