#include <iostream>
#include <memory>

// Abstract product interfaces
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Color {
public:
    virtual void fill() const = 0;
    virtual ~Color() = default;
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

class Red : public Color {
public:
    void fill() const override { std::cout << "Filling with Red color." << std::endl; }
};

class Blue : public Color {
public:
    void fill() const override { std::cout << "Filling with Blue color." << std::endl; }
};

class Green : public Color {
public:
    void fill() const override { std::cout << "Filling with Green color." << std::endl; }
};

// Abstract Factory
class AbstractFactory {
public:
    virtual std::unique_ptr<Shape> createShape() = 0;
    virtual std::unique_ptr<Color> createColor() = 0;
    virtual ~AbstractFactory() = default;
};

// Concrete Factories
class CircleFactory : public AbstractFactory {
public:
    std::unique_ptr<Shape> createShape() override { return std::make_unique<Circle>(); }
    std::unique_ptr<Color> createColor() override { return std::make_unique<Red>(); }
};

class SquareFactory : public AbstractFactory {
public:
    std::unique_ptr<Shape> createShape() override { return std::make_unique<Square>(); }
    std::unique_ptr<Color> createColor() override { 
        // Updated to include Green
        return std::make_unique<Green>(); 
    }
};

// Client code
int main() {
    std::unique_ptr<AbstractFactory> factory1 = std::make_unique<CircleFactory>();
    auto shape1 = factory1->createShape();
    auto color1 = factory1->createColor();

    shape1->draw();
    color1->fill();

    std::unique_ptr<AbstractFactory> factory2 = std::make_unique<SquareFactory>();
    auto shape2 = factory2->createShape();
    auto color2 = factory2->createColor();

    shape2->draw();
    color2->fill();

    return 0;
}
