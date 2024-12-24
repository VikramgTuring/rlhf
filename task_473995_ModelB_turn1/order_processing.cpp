#include <cstdio>

// Function prototype for updating inventory (declared in inventory_management.h)
extern void update_inventory(const char* product_name, int quantity);

void process_order(const char* product_name, int quantity_ordered) {
    printf("Order Processing: Received order for %s (%d units)\n", product_name, quantity_ordered);

    // Simulate some order processing logic

    // Call the inventory management module to update inventory
    update_inventory(product_name, quantity_ordered);

    printf("Order Processing: Order for %s processed successfully.\n", product_name);
}
