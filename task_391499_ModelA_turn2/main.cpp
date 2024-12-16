#include <iostream>
#include <memory>
#include <chrono>
#include <vector>
#include <string>

// Base Movement Strategy
class MovementStrategy {
public:
    virtual void move() = 0;
    virtual ~MovementStrategy() = default;
};

// Swim behavior
class SwimBehavior {
public:
    void swim() {
        std::cout << "Swimming...\n";
    }
};

// Climb behavior
class ClimbBehavior {
public:
    void climb() {
        std::cout << "Climbing...\n";
    }
};

// Implementation for Movement Strategy
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

// Character that uses multiple behaviors
class Character {
private:
    std::unique_ptr<MovementStrategy> movementStrategy;
    std::unique_ptr<SwimBehavior> swimBehavior;
    std::unique_ptr<ClimbBehavior> climbBehavior;

public:
    void setMovementStrategy(std::unique_ptr<MovementStrategy> strategy) {
        movementStrategy = std::move(strategy);
    }

    void setSwimBehavior(std::unique_ptr<SwimBehavior> behavior) {
        swimBehavior = std::move(behavior);
    }

    void setClimbBehavior(std::unique_ptr<ClimbBehavior> behavior) {
        climbBehavior = std::move(behavior);
    }

    void move() {
        if (movementStrategy) {
            movementStrategy->move();
        } else {
            std::cout << "No movement strategy set!\n";
        }
    }

    void swim() {
        if (swimBehavior) {
            swimBehavior->swim();
        }
    }

    void climb() {
        if (climbBehavior) {
            climbBehavior->climb();
        }
    }
};

// Main function
int main() {
    Character character;

    character.setMovementStrategy(std::make_unique<WalkStrategy>());
    character.move();

    character.setMovementStrategy(std::make_unique<RunStrategy>());
    character.move();

    character.setMovementStrategy(std::make_unique<FlyStrategy>());
    character.move();

    character.setSwimBehavior(std::make_unique<SwimBehavior>());
    character.swim();

    character.setClimbBehavior(std::make_unique<ClimbBehavior>());
    character.climb();

    return 0;
}
