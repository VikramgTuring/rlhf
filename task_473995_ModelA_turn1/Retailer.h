#ifndef RETAILER_H

#define RETAILER_H


#include <iostream>

#include "Supplier.h"


class Retailer {

private:

    Supplier* supplier;

public:

    Retailer(Supplier* supp): supplier(supp) { }


    void orderProduct(const std::string& product, int quantity) {

        // Debugging output to track order action

        printf("Retailer: Ordering %d units of %s\n", quantity, product.c_str());

        

        // Call the Supplier to supply the product

        supplier->supplyProduct(product, quantity);


        // Further processing after receiving the supply

        printf("Retailer: Received %d units of %s\n", quantity, product.c_str());

    }

};


#endif // RETAILER_H
