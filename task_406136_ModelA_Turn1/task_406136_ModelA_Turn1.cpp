#include <iostream>
#include <memory>
#include <string>

// Abstract Product
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
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
    virtual std::unique_ptr<Shape> createShape(const std::string& shapeType) = 0;
    virtual ~ShapeFactory() = default;
};

// Concrete Factories
class CircleFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape(const std::string& shapeType) override {
        if (shapeType == "CIRCLE") {
            return std::make_unique<Circle>();
        }
        else {
            throw std::runtime_error("Invalid shape type");
        }
    }
};

class SquareFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createShape(const std::string& shapeType) override {
        if (shapeType == "SQUARE") {
            return std::make_unique<Square>();
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
        std::unique_ptr<Shape> shape = factory->createShape(shapeType);
        shape->draw();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    delete factory;
    return 0;
}