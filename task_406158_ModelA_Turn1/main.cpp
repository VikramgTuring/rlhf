#include <iostream>
#include <memory>

class Foo {
public:
    Foo() {
        std::cout << "Foo constructor called." << std::endl;
    }

    ~Foo() {
        std::cout << "Foo destructor called." << std::endl;
    }
};

int main() {
    // Using std::unique_ptr to manage dynamically allocated memory
    {
        std::unique_ptr<Foo> ptr = std::make_unique<Foo>();
    } // ptr goes out of scope, and the destructor is automatically called

    // C-style pointer example that can lead to memory leaks if not managed properly
    {
        Foo* rawPtr = new Foo();
        // If we forget to delete rawPtr, it will cause a memory leak
        // delete rawPtr;
    }

    std::cout << "Program execution complete." << std::endl;
    return 0;
}
