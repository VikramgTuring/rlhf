
#include <iostream>
#include <vector>
#include <chrono>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    double area() override { return length * width; }
private:
    double length;
    double width;
};

class Circle : public Shape {
public:
    Circle(double r) : radius(r) {}
    double area() override { return 3.14 * radius * radius; }
private:
    double radius;
};

enum class ShapeType { Rectangle, Circle };

double staticDispatch(double val1, double val2, ShapeType type) {
    switch (type) {
        case ShapeType::Rectangle:
            return val1 * val2;
        case ShapeType::Circle:
            return 3.14 * val1 * val1;
    }
}

double dynamicDispatch(double val1, double val2, Shape* shape) {
    return shape->area();
}

int main() {
    const int numShapes = 1000000;
    std::vector<Shape*> shapes;
    std::vector<ShapeType> types;
    for (int i = 0; i < numShapes; ++i) {
        if (i % 2 == 0) {
            shapes.push_back(new Rectangle(1.0, 1.0));
            types.push_back(ShapeType::Rectangle);
        } else {
            shapes.push_back(new Circle(1.0));
            types.push_back(ShapeType::Circle);
        }
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numShapes; ++i) {
            double val1 = 1.0, val2 = 1.0;
            staticDispatch(val1, val2, types[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Static dispatch time: " << duration.count() << " microseconds" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < numShapes; ++i) {
            double val1 = 1.0, val2 = 1.0;
            dynamicDispatch(val1, val2, shapes[i]);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Dynamic dispatch time: " << duration.count() << " microseconds" << std::endl;
    }

    for (auto shape : shapes) {
        delete shape;
    }
    return 0;
}

