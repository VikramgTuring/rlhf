#include <iostream>
#include <memory>

// Example class for dynamic allocation
class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructor called." << std::endl;
    }
    ~MyClass() {
        std::cout << "MyClass destructor called." << std::endl;
    }
};

int main() {
    // Using std::unique_ptr to manage dynamically allocated memory
    {
        std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>();
        // ptr will automatically delete the object when it goes out of scope
    }

    std::cout << "Program end." << std::endl;
    return 0;
}
