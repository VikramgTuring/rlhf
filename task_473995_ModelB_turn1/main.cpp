#include <cstdio>

#include "order_processing.h"
#include "inventory_management.h"

int main() {
    const char* product1 = "Widgets";
    const char* product2 = "Gadgets";

    printf("Main: Starting supply chain management system.\n");

    process_order(product1, 10);
    process_order(product2, 5);
    process_order(product1, 7);

    printf("Main: Supply chain management system shutdown.\n");

    return 0;
}
