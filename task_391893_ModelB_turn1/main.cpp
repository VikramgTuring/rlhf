#include <iostream>
#include <memory>

class ThirdPartyIntegration {
public:
    static ThirdPartyIntegration* getInstance() {
        if (!instance) {
            instance = new ThirdPartyIntegration();
        }
        return instance;
    }

    // Private constructor to prevent direct instantiation from outside the class
    ThirdPartyIntegration() = default;

    ~ThirdPartyIntegration() = default;

    // Make the copy constructor and copy assignment operator private to prevent copying
    ThirdPartyIntegration(const ThirdPartyIntegration&) = delete;
    ThirdPartyIntegration& operator=(const ThirdPartyIntegration&) = delete;

    // Member functions to interact with the third-party service
    void initializeIntegration() {
        std::cout << "Initializing integration with third-party service..." << std::endl;
    }

    void sendDataToThirdParty(const std::string& data) {
        std::cout << "Sending data to third-party service: " << data << std::endl;
    }

private:
    static ThirdPartyIntegration* instance;
};

ThirdPartyIntegration* ThirdPartyIntegration::instance = nullptr;

int main() {
    ThirdPartyIntegration* integration1 = ThirdPartyIntegration::getInstance();
    ThirdPartyIntegration* integration2 = ThirdPartyIntegration::getInstance();

    // Check if both pointers point to the same instance (Singleton)
    if (integration1 == integration2) {
        std::cout << "Singleton instance working correctly." << std::endl;
    } else {
        std::cout << "Singleton instance creation failed." << std::endl;
        return 1;
    }

    integration1->initializeIntegration();
    integration1->sendDataToThirdParty("Hello from the cloud!");

    return 0;
}
