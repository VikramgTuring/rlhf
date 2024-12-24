#include <iostream>

#include "Supplier.h"

#include "Retailer.h"


int main() {

    Supplier supplier;

    Retailer retailer(&supplier);


    // Retailer tries to order products

    retailer.orderProduct("Widgets", 100);

    retailer.orderProduct("Gadgets", 50);


    return 0;

}
