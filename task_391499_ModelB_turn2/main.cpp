#include <iostream>
#include <memory>
#include <string>

class MovementStrategy {
public:
    virtual ~MovementStrategy() = default;
    virtual void move() = 0;
    virtual std::string getDescription() const = 0;
};

class LandMovementStrategy : public MovementStrategy {
public:
    void move() override {
        std::cout << "Moving on land... ";
    }

    std::string getDescription() const override {
        return "Land Movement";
    }
};

class AirMovementStrategy : public MovementStrategy {
public:
    void move() override {
        std::cout << "Moving in air... ";
    }

    std::string getDescription() const override {
        return "Air Movement";
    }
};

class WalkStrategy : public LandMovementStrategy {
public:
    void move() override {
        LandMovementStrategy::move();
        std::cout << "Walking.\n";
    }

    std::string getDescription() const override {
        return "Walking";
    }
};

class RunStrategy : public LandMovementStrategy {
public:
    void move() override {
        LandMovementStrategy::move();
        std::cout << "Running.\n";
    }

    std::string getDescription() const override {
        return "Running";
    }
};

class FlyStrategy : public AirMovementStrategy {
public:
    void move() override {
        AirMovementStrategy::move();
        std::cout << "Flying.\n";
    }

    std::string getDescription() const override {
        return "Flying";
    }
};

class SwimStrategy : public LandMovementStrategy {
public:
    void move() override {
        LandMovementStrategy::move();
        std::cout << "Swimming.\n";
    }

    std::string getDescription() const override {
        return "Swimming";
    }
};

class ClimbStrategy : public LandMovementStrategy {
public:
    void move() override {
        LandMovementStrategy::move();
        std::cout << "Climbing.\n";
    }

    std::string getDescription() const override {
        return "Climbing";
    }
};

class MovementStrategyFactory {
public:
    static std::unique_ptr<MovementStrategy> createStrategy(const std::string& strategyType) {
        if (strategyType == "walk") {
            return std::make_unique<WalkStrategy>();
        } else if (strategyType == "run") {
            return std::make_unique<RunStrategy>();
        } else if (strategyType == "fly") {
            return std::make_unique<FlyStrategy>();
        } else if (strategyType == "swim") {
            return std::make_unique<SwimStrategy>();
        } else if (strategyType == "climb") {
            return std::make_unique<ClimbStrategy>();
        } else {
            throw std::runtime_error("Invalid strategy type");
        }
    }
};

int main() {
    Character character;

    character.setMovementStrategy(MovementStrategyFactory::createStrategy("walk"));
    character.move();

    character.setMovementStrategy(MovementStrategyFactory::createStrategy("run"));
    character.move();

    character.setMovementStrategy(MovementStrategyFactory::createStrategy("fly"));
    character.move();

    character.setMovementStrategy(MovementStrategyFactory::createStrategy("swim"));
    character.move();

    character.setMovementStrategy(MovementStrategyFactory::createStrategy("climb"));
    character.move();

    return 0;
}
