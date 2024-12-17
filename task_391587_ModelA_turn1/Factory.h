#include <string>
#include <unordered_map>

class Product {
public:
    virtual void doSomething() = 0;
};

class ConcreteProductA : public Product {
public:
    void doSomething() override {
        // Implementation of A
    }
};

class ConcreteProductB : public Product {
public:
    void doSomething() override {
        // Implementation of B
    }
};

class Factory {
public:
    static std::unique_ptr<Product> createProduct(const std::string& type) {
        if (type == "A") return std::make_unique<ConcreteProductA>();
        else if (type == "B") return std::make_unique<ConcreteProductB>();
        return nullptr;
    }
};
