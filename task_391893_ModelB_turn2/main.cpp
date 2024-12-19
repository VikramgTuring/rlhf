#include <iostream>
#include <string>
#include <memory> // For unique_ptr
#include <mutex>

// Abstract Interface for each ThirdPartyService
class ThirdPartyService {
public:
    virtual ~ThirdPartyService() = default;

    // Method to perform a service-specific action
    virtual void PerformServiceAction(const std::string& action) = 0;

    virtual std::string GetServiceState() = 0;
};

// EC2 Service implementation
class EC2Service : public ThirdPartyService {
private:
    std::string state = "Offline";

public:
    void PerformServiceAction(const std::string& action) override {
        if (action == "StartInstance") {
            state = "Online";
            std::cout << "EC2 instance started." << std::endl;
        } else {
            std::cout << "Invalid action for EC2." << std::endl;
        }
    }

    std::string GetServiceState() override {
        return state;
    }
};

// RDS Service implementation
class RDSService : public ThirdPartyService {
private:
    std::string state = "Initializing";

public:
    void PerformServiceAction(const std::string& action) override {
        if (action == "Connect") {
            state = "Connected";
            std::cout << "RDS database connected." << std::endl;
        } else {
            std::cout << "Invalid action for RDS." << std::endl;
        }
    }

    std::string GetServiceState() override {
        return state;
    }
};

// Abstract Factory class
class ServiceFactory {
public:
    virtual ~ServiceFactory() = default;

    virtual std::unique_ptr<ThirdPartyService> CreateEC2Service() = 0;
    virtual std::unique_ptr<ThirdPartyService> CreateRDSService() = 0;
};

// Concrete Factory implementation
class ConcreteServiceFactory : public ServiceFactory {
public:
    std::unique_ptr<ThirdPartyService> CreateEC2Service() override {
        return std::make_unique<EC2Service>();
    }

    std::unique_ptr<ThirdPartyService> CreateRDSService() override {
        return std::make_unique<RDSService>();
    }
};

// Singleton classes for the Services
class EC2ServiceManager {
private:
    static EC2ServiceManager* instance;
    static std::mutex mutex;
    std::unique_ptr<EC2Service> service;

    EC2ServiceManager(ServiceFactory* factory) : service(factory->CreateEC2Service()) {}

public:
    ~EC2ServiceManager() = default;

    EC2ServiceManager(const EC2ServiceManager&) = delete;
    EC2ServiceManager& operator=(const EC2ServiceManager&) = delete;
