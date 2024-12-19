#include <iostream>
#include <cstring>

using namespace std;

const int MAX_NAME_LENGTH = 16;
const int MAX_ADDRESS_LENGTH = 32;

struct Person {
    char name[MAX_NAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
};

// Safe version of string copy
void safeStrCpy(char* dest, const char* src, size_t destSize) {
    if (destSize > 0) {
        // Copy using strncpy to avoid overflow
        strncpy(dest, src, destSize - 1);  // Leave space for null terminator
        dest[destSize - 1] = '\0'; // Ensure null-termination
    }
}

// Function to get string length
size_t safeStrLen(const char* str) {
    return strlen(str); // Safe for null-terminated strings
}

// Function to display person information
void printPersonInfo(const Person& person) {
    cout << "Name: " << person.name << ", Address: " << person.address << endl;
}

int main() {
    Person person;

    // Use safe string copy to set the name
    const char* exampleName = "John Doe";
    safeStrCpy(person.name, exampleName, sizeof(person.name));

    // Use safe string copy to set the address
    const char* exampleAddress = "1234 Main St, Anytown, USA";
    safeStrCpy(person.address, exampleAddress, sizeof(person.address));

    // Print the length of the name and address
    cout << "Name Length: " << safeStrLen(person.name) << endl;
    cout << "Address Length: " << safeStrLen(person.address) << endl;

    // Print the person information
    printPersonInfo(person);

    return 0;
}
