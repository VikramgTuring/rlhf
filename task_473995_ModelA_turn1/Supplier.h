#ifndef SUPPLIER_H

#define SUPPLIER_H


#include <iostream>


class Supplier {

public:

    void supplyProduct(const std::string& product, int quantity) {

        // Debugging output to track supply action

        printf("Supplier: Supplying %d units of %s\n", quantity, product.c_str());

        

        // Supply logic implementation

        // Assuming supply is always successful for simplification

        // Notify Retailer here if necessary or let Retailer call this function to supply products

    }

};


#endif // SUPPLIER_H
