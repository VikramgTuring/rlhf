#include <iostream>

// Abstract Product
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

// Concrete Products
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a square." << std::endl;
    }
};

// Abstract Factory
class ShapeFactory {
public:
    virtual Shape& createShape(const std::string& shapeType) = 0;
    virtual ~ShapeFactory() = default;
};

// Concrete Factories
class CircleFactory : public ShapeFactory {
private:
    Circle circle;

public:
    Shape& createShape(const std::string& shapeType) override {
        if (shapeType == "CIRCLE") {
            return circle;
        }
        else {
            throw std::runtime_error("Invalid shape type");
        }
    }
};

class SquareFactory : public ShapeFactory {
private:
    Square square;

public:
    Shape& createShape(const std::string& shapeType) override {
        if (shapeType == "SQUARE") {
            return square;
        }
        else {
            throw std::runtime_error("Invalid shape type");
        }
    }
};

int main() {
    ShapeFactory* factory = nullptr;

    std::string shapeType;
    std::cout << "Enter shape type (CIRCLE/SQUARE): ";
    std::getline(std::cin, shapeType);

    if (shapeType == "CIRCLE") {
        factory = new CircleFactory();
    }
    else if (shapeType == "SQUARE") {
        factory = new SquareFactory();
    }
    else {
        std::cout << "Invalid shape type." << std::endl;
        return 1;
    }

    try {
        Shape& shape = factory->createShape(shapeType);
        shape.draw();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    delete factory;
    return 0;
}