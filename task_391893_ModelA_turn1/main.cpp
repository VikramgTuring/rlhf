#include <iostream>
#include <mutex>

class ThirdPartyService {
public:
    // Public method to interact with the third-party service
    void RequestData() {
        std::cout << "Fetching data from third-party service..." << std::endl;
    }

    // ... Other methods to interact with the service can be added here ...
};

class ThirdPartyServiceManager {
private:
    static ThirdPartyServiceManager* instance;
    static std::mutex mutex;

    // Private constructor to prevent direct instantiation
    ThirdPartyServiceManager() {
        // Initialize connections or states here if needed
    }

public:
    // Delete copy constructor and assignment operator
    ThirdPartyServiceManager(const ThirdPartyServiceManager &) = delete;
    ThirdPartyServiceManager &operator=(const ThirdPartyServiceManager &) = delete;

    // Public method to provide access to the instance
    static ThirdPartyServiceManager* GetInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex); // Ensure thread safety
            if (instance == nullptr) { // Double-checked locking
                instance = new ThirdPartyServiceManager();
            }
        }
        return instance;
    }

    // Method to set up a ThirdPartyService instance (more application-specific logic)
    void PerformServiceRequest() {
        ThirdPartyService service; // Using a new instance per request if stateless
        service.RequestData();
        // Handle response and errors as needed
    }
};

// Initialize the static member
ThirdPartyServiceManager* ThirdPartyServiceManager::instance = nullptr;
std::mutex ThirdPartyServiceManager::mutex;

// Usage of the Singleton
int main() {
    ThirdPartyServiceManager* manager = ThirdPartyServiceManager::GetInstance();
    manager->PerformServiceRequest(); // Perform a request through the service manager

    return 0;
}
