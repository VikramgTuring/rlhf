#include <iostream>
#include <memory>
#include <chrono>

// The Strategy interface
class MovementStrategy {
public:
    virtual void move() = 0; // Perform the movement action
    virtual ~MovementStrategy() = default;
};

// Concrete strategies
class WalkStrategy : public MovementStrategy {
public:
    void move() override {
        std::cout << "Walking...\n";
    }
};

class RunStrategy : public MovementStrategy {
public:
    void move() override {
        std::cout << "Running...\n";
    }
};

class FlyStrategy : public MovementStrategy {
public:
    void move() override {
        std::cout << "Flying...\n";
    }
};

// Context that uses the strategy
class Character {
private:
    std::unique_ptr<MovementStrategy> movementStrategy;

public:
    void setMovementStrategy(std::unique_ptr<MovementStrategy> strategy) {
        movementStrategy = std::move(strategy);
    }

    void move() {
        if (movementStrategy) {
            movementStrategy->move();
        } else {
            std::cout << "No movement strategy set!\n";
        }
    }
};

// Function to measure performance
void measurePerformance(const std::unique_ptr<MovementStrategy>& strategy, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        strategy->move();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    
    std::cout << "Performance for " << typeid(*strategy).name() << ": " << duration.count() << " ms\n";
}

// Main program
int main() {
    Character character;

    character.setMovementStrategy(std::make_unique<WalkStrategy>());
    character.move();
    
    // Measure performance of WALK
    measurePerformance(character.movementStrategy, 1000000); // change iterations as needed

    character.setMovementStrategy(std::make_unique<RunStrategy>());
    character.move();
    
    // Measure performance of RUN
    measurePerformance(character.movementStrategy, 1000000); // change iterations as needed

    character.setMovementStrategy(std::make_unique<FlyStrategy>());
    character.move();

    // Measure performance of FLY
    measurePerformance(character.movementStrategy, 1000000); // change iterations as needed

    return 0;
}
