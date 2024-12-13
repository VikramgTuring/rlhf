#include <iostream>
#include <memory>

// The product interface
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Concrete products
class Circle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Circle." << std::endl; }
};

class Square : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Square." << std::endl; }
};

// Factory
class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& type) {
        if (type == "Circle") {
            return std::make_unique<Circle>();
        } else if (type == "Square") {
            return std::make_unique<Square>();
        }
        return nullptr;
    }
};

// Client code
int main() {
    auto shape1 = ShapeFactory::createShape("Circle");
    shape1->draw();

    auto shape2 = ShapeFactory::createShape("Square");
    shape2->draw();

    return 0;
}
