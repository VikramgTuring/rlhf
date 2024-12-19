#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Abstract interface for cloud services
class CloudService {
public:
    virtual void initialize() = 0;
    virtual void execute() = 0;
    virtual ~CloudService() = default;
};

// EC2 service implementation
class EC2Service : public CloudService {
public:
    void initialize() override {
        std::cout << "Initializing EC2 Service" << std::endl;
    }

    void execute() override {
        std::cout << "Executing operations on EC2 instances" << std::endl;
    }
};

// RDS service implementation
class RDSService : public CloudService {
public:
    void initialize() override {
        std::cout << "Initializing RDS Service" << std::endl;
    }

    void execute() override {
        std::cout << "Executing operations on RDS databases" << std::endl;
    }
};

// Facade class to interact with multiple services
class CloudFacade {
private:
    std::unique_ptr<CloudService> ec2Service;
    std::unique_ptr<CloudService> rdsService;

public:
    CloudFacade() {
        // Initialize services
        ec2Service = std::make_unique<EC2Service>();
        rdsService = std::make_unique<RDSService>();
    }

    void initializeServices() {
        ec2Service->initialize();
        rdsService->initialize();
    }

    void executeAll() {
        ec2Service->execute();
        rdsService->execute();
    }
};

// Usage of the facade
int main() {
    CloudFacade cloudFacade;
    
    // Initialize services
    cloudFacade.initializeServices();
    
    // Execute operations on all services
    cloudFacade.executeAll();

    return 0;
}
