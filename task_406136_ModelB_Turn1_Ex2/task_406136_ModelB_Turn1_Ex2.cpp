#include <iostream>

// Base Shape class (unchanged)

// Concrete Shape classes (unchanged)

// ShapeFactory (modified to use stack allocation)
class ShapeFactory {
public:
    static Shape& createShape(Shape::ShapeType type) {
        switch (type) {
        case Shape::CIRCLE:
            return *new (&shapeBuffer) Circle(); // Placement new on stack
        case Shape::SQUARE:
            return *new (&shapeBuffer) Square(); // Placement new on stack
        default:
            throw std::runtime_error("Invalid shape type");
        }
    }

private:
    static union {
        Circle circle;
        Square square;
    } shapeBuffer;
};

int main() {
    try {
        Shape& circle = ShapeFactory::createShape(Shape::CIRCLE);
        circle.draw();

        Shape& square = ShapeFactory::createShape(Shape::SQUARE);
        square.draw();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}