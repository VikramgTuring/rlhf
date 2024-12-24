#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

// Define log levels
enum LogLevel {
    LOG_ERROR = 0,
    LOG_WARNING = 1,
    LOG_INFO = 2,
    LOG_DEBUG = 3,
};

void logMessage(LogLevel level, const char* file, int line, const char* format, ...) {
    time_t now = time(0);
    struct tm* tm = localtime(&now);
    char timestamp[16];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm);

    va_list args;
    va_start(args, format);

    switch (level) {
        case LOG_ERROR:
            printf("[%s][%s:%d][ERROR] ", timestamp, file, line);
            break;
        case LOG_WARNING:
            printf("[%s][%s:%d][WARNING] ", timestamp, file, line);
            break;
        case LOG_INFO:
            printf("[%s][%s:%d][INFO] ", timestamp, file, line);
            break;
        case LOG_DEBUG:
            printf("[%s][%s:%d][DEBUG] ", timestamp, file, line);
            break;
        default:
            printf("[%s][%s:%d][UNKNOWN] ", timestamp, file, line);
            break;
    }
    vprintf(format, args);
    printf("\n");

    va_end(args);
}

// Supplier.h
#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>

class Supplier {
public:
    void supplyProduct(const std::string& product, int quantity) {
        const char* file = __FILE__;
        int line = __LINE__;
        logMessage(LOG_INFO, file, line, "Supplier: Supplying %d units of %s", quantity, product.c_str());

        // Simulate an error condition
        if (quantity == 0) {
            logMessage(LOG_ERROR, file, line, "Supplier: Error: Cannot supply zero units of %s", product.c_str());
            return;
        }
    }
};

#endif // SUPPLIER_H

// Retailer.h
#ifndef RETAILER_H
#define RETAILER_H

#include <iostream>
#include "Supplier.h"

class Retailer {
private:
    Supplier* supplier;
public:
    Retailer(Supplier* supp) : supplier(supp) { }

    void orderProduct(const std::string& product, int quantity) {
        const char* file = __FILE__;
        int line = __LINE__;
        logMessage(LOG_INFO, file, line, "Retailer: Ordering %d units of %s", quantity, product.c_str());

        if (quantity <= 0) {
            logMessage(LOG_WARNING, file, line, "Retailer: Invalid order: Quantity must be positive");
            return;
        }

        supplier->supplyProduct(product, quantity);

        logMessage(LOG_INFO, file, line, "Retailer: Received %d units of %s", quantity, product.c_str());
    }
};

#endif // RETAILER_H

// main.cpp
#include <iostream>
#include "Supplier.h"
#include "Retailer.h"

int main() {
    Supplier supplier;
    Retailer retailer(&supplier);

    retailer.orderProduct("Widgets", 100);
    retailer.orderProduct("Gadgets", 0); // Will trigger an error in Supplier
    retailer.orderProduct("Sprockets", -10); // Will trigger a warning in Retailer

    return 0;
}
