#include <iostream>
#include <memory>

// Base class
class Enemy {
public:
    virtual void attack() = 0;
    virtual ~Enemy() = default;
};

// Concrete classes
class Goblin : public Enemy {
public:
    void attack() override {
        std::cout << "Goblin attacks!" << std::endl;
    }
};

class Orc : public Enemy {
public:
    void attack() override {
        std::cout << "Orc attacks!" << std::endl;
    }
};

// Factory class
class EnemyFactory {
public:
    virtual std::unique_ptr<Enemy> createEnemy(EnemyType type) = 0;
    virtual ~EnemyFactory() = default;
};

enum class EnemyType {
    GOBLIN,
    ORC
};

class SimpleEnemyFactory : public EnemyFactory {
public:
    std::unique_ptr<Enemy> createEnemy(EnemyType type) override {
        switch (type) {
            case EnemyType::GOBLIN:
                return std::make_unique<Goblin>();
            case EnemyType::ORC:
                return std::make_unique<Orc>();
        }
        return nullptr;
    }
};

int main() {
    EnemyFactory* factory = new SimpleEnemyFactory();
    std::unique_ptr<Enemy> enemy1 = factory->createEnemy(EnemyType::GOBLIN);
    std::unique_ptr<Enemy> enemy2 = factory->createEnemy(EnemyType::ORC);

    enemy1->attack(); // Output: Goblin attacks!
    enemy2->attack(); // Output: Orc attacks!

    delete factory;
    return 0;
}
