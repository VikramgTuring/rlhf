#include <iostream>
#include <memory>
#include <chrono>
#include <string>
#include <vector>

// Base class for the Strategy Pattern
class MovementStrategy {
public:
    virtual ~MovementStrategy() = default;

    virtual void move() = 0;

    virtual std::string getName() const = 0;
};

// Concrete Strategy 1: Simple movement
class SimpleMovement : public MovementStrategy {
public:
    void move() override {
        std::cout << "Moving simply." << std::endl;
    }

    std::string getName() const override {
        return "Simple Movement";
    }
};

// Concrete Strategy 2: Advanced movement with AI
class AdvancedMovement : public MovementStrategy {
public:
    void move() override {
        std::cout << "Moving with advanced AI." << std::endl;
    }

    std::string getName() const override {
        return "Advanced Movement";
    }
};

// Context class that uses the Strategy
class Character {
private:
    std::unique_ptr<MovementStrategy> strategy_;

public:
    void setStrategy(std::unique_ptr<MovementStrategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void move() {
        strategy_->move();
    }

    std::string getStrategyName() const {
        return strategy_->getName();
    }
};

// Function to measure the performance of a strategy
double measureStrategyPerformance(const std::unique_ptr<MovementStrategy>& strategy) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < 1000000; ++i) {
        strategy->move();
    }
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<duration<double, nano>>(end - start);
    return duration.count() / 1'000'000; // Return in milliseconds
}

int main() {
    Character character;

    {
        // Simple Movement Strategy
        std::unique_ptr<MovementStrategy> simpleStrategy = std::make_unique<SimpleMovement>();
        character.setStrategy(std::move(simpleStrategy));

        std::cout << "Using " << character.getStrategyName() << std::endl;
        character.move();

        double simpleTime = measureStrategyPerformance(character.strategy_);
        std::cout << "Performance of " << character.getStrategyName() << ": " << simpleTime << " ms" << std::endl;
    }

    {
        // Advanced Movement Strategy
        std::unique_ptr<MovementStrategy> advancedStrategy = std::make_unique<AdvancedMovement>();
        character.setStrategy(std::move(advancedStrategy));

        std::cout << "\nUsing " << character.getStrategyName() << std::endl;
        character.move();

        double advancedTime = measureStrategyPerformance(character.strategy_);
        std::cout << "Performance of " << character.getStrategyName() << ": " << advancedTime << " ms" << std::endl;
    }

    return 0;
}
