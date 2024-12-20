#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// Example of a complex user-defined class
class ComplexData {
public:
    int id;
    char* name; // dynamically allocated memory
    vector<int> numbers; // a container

    // Constructor
    ComplexData(int id, const char* name) : id(id), numbers() {
        this->name = new char[strlen(name) + 1]; // allocate memory for name
        strcpy(this->name, name);
    }

    // Copy constructor (deep copy)
    ComplexData(const ComplexData& other) : id(other.id), numbers(other.numbers) {
        name = new char[strlen(other.name) + 1]; // allocate new memory
        strcpy(name, other.name);
    }

    // Destructor
    ~ComplexData() {
        delete[] name; // free the allocated memory
    }

    // Print method for demonstration purposes
    void print() const {
        cout << "ID: " << id << ", Name: " << name << ", Numbers: ";
        for (auto num : numbers) {
            cout << num << " ";
        }
        cout << endl;
    }
};

// Template to clone an array of complex data
template <typename T>
T* cloneArray(const T* arr, size_t size) {
    T* clonedArray = new T[size]; // allocate memory for the cloned array
    for (size_t i = 0; i < size; i++) {
        clonedArray[i] = arr[i]; // use the copy constructor for deep copy
    }
    return clonedArray;
}

int main() {
    // Create an array of ComplexData
    const size_t arraySize = 3;
    ComplexData complexArray[arraySize] = {
        ComplexData(1, "Alice"),
        ComplexData(2, "Bob"),
        ComplexData(3, "Charlie"),
    };

    // Populate the numbers vector in each ComplexData object
    for (size_t i = 0; i < arraySize; ++i) {
        complexArray[i].numbers.push_back(i * 10);
        complexArray[i].numbers.push_back(i * 10 + 1);
    }

    // Clone the None complex array
    ComplexData* clonedArray = cloneArray(complexArray, arraySize);

    // Demonstrate the functionality
    for (size_t i = 0; i < arraySize; ++i) {
        cout << "Original Array Element " << i << ":\n";
        complexArray[i].print();
        
        cout << "Cloned Array Element " << i << ":\n";
        clonedArray[i].print();
    }

    // Clean up dynamically allocated memory
    delete[] clonedArray;

    return 0;
}
