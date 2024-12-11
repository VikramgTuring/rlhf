// Base protocol interface
class SecurityProtocol {
public:
    virtual ~SecurityProtocol() = default;

    virtual void encrypt(const std::string& data) = 0;
    virtual void decrypt(const std::string& data) = 0;
};

// Concrete protocol implementations
class AESProtocol : public SecurityProtocol {
public:
    void encrypt(const std::string& data) override {
        // AES encryption logic
    }

    void decrypt(const std::string& data) override {
        // AES decryption logic
    }
};

class TLSProtocol : public SecurityProtocol {
public:
    void encrypt(const std::string& data) override {
        // TLS encryption logic
    }

    void decrypt(const std::string& data) override {
        // TLS decryption logic
    }
};

// Protocol factory
class SecurityProtocolFactory {
public:
    enum class ProtocolType {
        AES,
        TLS,
    };

    static std::unique_ptr<SecurityProtocol> createProtocol(ProtocolType type) {
        switch (type) {
            case ProtocolType::AES:
                return std::make_unique<AESProtocol>();
            case ProtocolType::TLS:
                return std::make_unique<TLSProtocol>();
            default:
                throw std::runtime_error("Invalid protocol type");
        }
    }
};

// Example usage
int main() {
    std::cout << "Select security protocol:\n";
    std::cout << "1. AES\n";
    std::cout << "2. TLS\n";
    int choice;
    std::cin >> choice;

    SecurityProtocolFactory::ProtocolType protocolType;
    switch (choice) {
        case 1:
            protocolType = SecurityProtocolFactory::ProtocolType::AES;
            break;
        case 2:
            protocolType = SecurityProtocolFactory::ProtocolType::TLS;
            break;
        default:
            std::cout << "Invalid choice.\n";
            return 1;
    }

    try {
        auto protocol = SecurityProtocolFactory::createProtocol(protocolType);
        std::string data = "This is some secret data";

        protocol->encrypt(data);
        // Perform other operations using the protocol object

        std::cout << "Data encrypted successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
