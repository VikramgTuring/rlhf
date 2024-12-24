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
