#include <iostream>

// Base Shape class
class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;

    virtual void draw() const = 0;
};

// Concrete Shape classes
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle." << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Square." << std::endl;
    }
};

// ShapeFactory
class ShapeFactory {
public:
    static Shape* createShape(Shape::ShapeType type) {
        switch (type) {
        case Shape::CIRCLE:
            return new Circle();  // Heap allocation
        case Shape::SQUARE:
            return new Square();  // Heap allocation
        default:
            return nullptr;
        }
    }
};

int main() {
    Shape* circle = ShapeFactory::createShape(Shape::CIRCLE);
    circle->draw();
    delete circle;  // Remember to delete the dynamically allocated object

    Shape* square = ShapeFactory::createShape(Shape::SQUARE);
    square->draw();
    delete square;  // Remember to delete the dynamically allocated object

    return 0;
}