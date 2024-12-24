#include <cstdio>
#include <string>
#include <ctime>

// Logging Macro
#define LOG(level, module, fmt, ...) \
    printf("[%s] [%s] " fmt "\n", getCurrentTime().c_str(), module, ##__VA_ARGS__)

// Function to get current time as string
std::string getCurrentTime() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}

// Supplier class
class Supplier {
public:
    void supplyProduct(const std::string& product, int quantity) {
        LOG("INFO", "Supplier", "Supplying %d units of %s", quantity, product.c_str());
        // Simulate successful supply operation
        LOG("INFO", "Supplier", "Supply operation completed for %d units of %s", quantity, product.c_str());
    }
};

// Retailer class
class Retailer {
private:
    Supplier* supplier;
public:
    Retailer(Supplier* supp) : supplier(supp) { }

    void orderProduct(const std::string& product, int quantity) {
        LOG("INFO", "Retailer", "Ordering %d units of %s", quantity, product.c_str());

        // Simulate an order processing step
        if (quantity <= 0) {
            LOG("ERROR", "Retailer", "Invalid quantity %d for product %s", quantity, product.c_str());
            return;
        }
        
        supplier->supplyProduct(product, quantity);

        // Further processing after receiving the products
        LOG("INFO", "Retailer", "Successfully received %d units of %s", quantity, product.c_str());
    }
};

// Main function
int main() {
    Supplier supplier;
    Retailer retailer(&supplier);

    retailer.orderProduct("Widgets", 100);
    retailer.orderProduct("Gadgets", -1);  // This should trigger an error

    return 0;
}
