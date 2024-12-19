#include <iostream>
#include <cstring>

#define MAX_NAME_LENGTH 50

// Define a struct to hold user data
struct User {
    char name[MAX_NAME_LENGTH];
    int age;

    // Method to set the name with proper bounds checking
    void setName(const char* newName) {
        // Ensure we do not exceed the maximum length
        strncpy(name, newName, MAX_NAME_LENGTH - 1);
        name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
    }

    // Method to print the user information
    void printInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    User user1;
    user1.age = 30;

    // Set the name using the setName method
    user1.setName("John Doe");

    // Print user information
    user1.printInfo();

    // Modify the name
    user1.setName("Alice Wonderland");
    user1.printInfo();

    return 0;
}
