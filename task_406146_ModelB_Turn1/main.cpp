#include <iostream>
#include <map>
#include <string>
#include <memory>

using namespace std;

// Abstract Protocol Class
class Protocol {
public:
    virtual ~Protocol() = default;

    virtual void processData() = 0;

    static string protocolType() {
        return "Protocol";
    }
};

// Concrete Protocol Implementations
class SSLProtocol : public Protocol {
public:
    void processData() override {
        cout << "Processing data using SSL protocol." << endl;
    }

    static string protocolType() {
        return "SSLProtocol";
    }
};

class TLSProtocol : public Protocol {
public:
    void processData() override {
        cout << "Processing data using TLS protocol." << endl;
    }

    static string protocolType() {
        return "TLSProtocol";
    }
};

// Factory Class
class ProtocolFactory {
private:
    map<string, function<shared_ptr<Protocol>()>> protocolCreators;

public:
    ProtocolFactory() {
        registerProtocol("SSL", make_shared<SSLProtocol>);
        registerProtocol("TLS", make_shared<TLSProtocol>);
    }

    void registerProtocol(const string& name, const function<shared_ptr<Protocol>()>& creator) {
        protocolCreators[name] = creator;
    }

    shared_ptr<Protocol> createProtocol(const string& protocolType) {
        auto creator = protocolCreators.find(protocolType);
        if (creator != protocolCreators.end()) {
            return creator->second();
        } else {
            cerr << "Invalid protocol type: " << protocolType << endl;
            return nullptr;
        }
    }
};

int main() {
    ProtocolFactory factory;

    string protocolType;
    cout << "Enter protocol type (SSL or TLS): ";
    getline(cin, protocolType);

    if (protocolType == "SSL" || protocolType == "TLS") {
        shared_ptr<Protocol> protocol = factory.createProtocol(protocolType);
        if (protocol) {
            protocol->processData();
        }
    } else {
        cout << "Invalid protocol type." << endl;
    }

    return 0;
}
