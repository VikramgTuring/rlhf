#include <iostream>
#include <memory>
#include <map>
#include <string>

// Step 1: Define a service interface
class IService {
public:
    virtual void Initialize() = 0; // Initialize service state
    virtual void FetchData() = 0; // Fetch data from the service
    virtual ~IService() {}
};

// Step 2: Implement concrete services
class ServiceA : public IService {
public:
    void Initialize() override {
        std::cout << "ServiceA initialized." << std::endl;
    }

    void FetchData() override {
        std::cout << "Fetching data from Service A." << std::endl;
    }
};

class ServiceB : public IService {
public:
    void Initialize() override {
        std::cout << "ServiceB initialized." << std::endl;
    }

    void FetchData() override {
        std::cout << "Fetching data from Service B." << std::endl;
    }
};

// Step 3: Factory to create services
class ServiceFactory {
public:
    static std::unique_ptr<IService> CreateService(const std::string& serviceType) {
        if (serviceType == "service_a") {
            return std::make_unique<ServiceA>();
        } else if (serviceType == "service_b") {
            return std::make_unique<ServiceB>();
        }
        return nullptr;
    }
};

// Step 4: Context class to use the services
class ServiceManager {
private:
    std::map<std::string, std::unique_ptr<IService>> services;

public:
    void AddService(const std::string& serviceType) {
        auto service = ServiceFactory::CreateService(serviceType);
        if (service) {
            service->Initialize(); // Initialize the service
            services[serviceType] = std::move(service); // Store the service instance
        } else {
            std::cerr << "Invalid service type: " << serviceType << std::endl;
        }
    }

    void FetchDataForAllServices() {
        for (auto& pair : services) {
            pair.second->FetchData(); // Call FetchData for each service
        }
    }
};

int main() {
    ServiceManager manager;

    // Register services dynamically
    manager.AddService("service_a");
    manager.AddService("service_b");

    // Fetch data from all registered services
    manager.FetchDataForAllServices();

    return 0;
}
