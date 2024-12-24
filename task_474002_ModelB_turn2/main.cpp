#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>

enum VerbosityLevel {
    LOG_LEVEL_OFF = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
};

struct CacheEntry {
    std::string ipAddress;
    time_t expiryTime;
};

class DnsCache {
public:
    DnsCache(VerbosityLevel verbosity = LOG_LEVEL_INFO) : verbosity(verbosity) {}

    void add(const std::string& domain, const std::string& ipAddress, int ttl) {
        time_t currentTime = time(nullptr);
        CacheEntry entry = { ipAddress, currentTime + ttl };
        cache[domain] = entry;
        log(LOG_LEVEL_INFO, "[CACHE ADD] Domain: %s, IP: %s, TTL: %d seconds", domain.c_str(), ipAddress.c_str(), ttl);
    }

    std::string resolve(const std::string& domain) {
        time_t currentTime = time(nullptr);
        auto it = cache.find(domain);
        
        if (it != cache.end()) {
            CacheEntry& entry = it->second;
            if (currentTime < entry.expiryTime) {
                log(LOG_LEVEL_DEBUG, "[CACHE HIT] Domain: %s, IP: %s, TTL Remaining: %ld seconds", 
                       domain.c_str(), entry.ipAddress.c_str(), 
                       entry.expiryTime - currentTime);
                return entry.ipAddress;
            } else {
                log(LOG_LEVEL_WARNING, "[CACHE MISS] Domain: %s has expired. Expired at %s", 
                       domain.c_str(), ctime(&entry.expiryTime));
                cache.erase(it);
            }
        } else {
            log(LOG_LEVEL_INFO, "[CACHE MISS] Domain: %s not found in cache.", domain.c_str());
        }
        return "";
    }

    void printCache() const {
        log(LOG_LEVEL_DEBUG, "[CACHE STATUS]\n");
        for (const auto& entry : cache) {
            log(LOG_LEVEL_DEBUG, "Domain: %s, IP: %s, Expires at: %s", 
                   entry.first.c_str(), entry.second.ipAddress.c_str(), 
                   ctime(&entry.second.expiryTime));
        }
    }

    void setVerbosity(VerbosityLevel level) {
        verbosity = level;
    }

private:
    void log(VerbosityLevel level, const char* format, ...) {
        if (level >= verbosity) {
            va_list args;
            va_start(args, format);
            printf("%s", ctime(&time(nullptr)));
            vprintf(format, args);
            va_end(args);
            printf("\n");
        }
    }

    std::unordered_map<std::string, CacheEntry> cache;
    VerbosityLevel verbosity;
};

int main() {
    DnsCache dnsCache;

    // Initialize with low verbosity for production
    dnsCache.setVerbosity(LOG_LEVEL_WARNING);

    dnsCache.add("example.com", "93.184.216.34", 10);
    dnsCache.add("openai.com", "104.18.25.178", 5);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    dnsCache.resolve("example.com");
