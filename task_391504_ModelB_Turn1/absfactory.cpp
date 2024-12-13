#include <iostream>
#include <memory>

// Base classes
class Unit {
public:
    virtual void attack() = 0;
    virtual ~Unit() = default;
};

class Soldier : public Unit {
public:
    void attack() override {
        std::cout << "Soldier attacks!" << std::endl;
    }
};

class Archer : public Unit {
public:
    void attack() override {
        std::cout << "Archer attacks!" << std::endl;
    }
};

class Mage : public Unit {
public:
    void attack() override {
        std::cout << "Mage attacks!" << std::endl;
    }
};

class AbstractFactory {
public:
    virtual std::unique_ptr<Soldier> createSoldier() = 0;
    virtual std::unique_ptr<Archer> createArcher() = 0;
    virtual std::unique_ptr<Mage> createMage() = 0;
    virtual ~AbstractFactory() = default;
};

// Concrete factories
class HumanFactory : public AbstractFactory {
public:
    std::unique_ptr<Soldier> createSoldier() override {
        return std::make_unique<HumanSoldier>();
    }

    std::unique_ptr<Archer> createArcher() override {
        return std::make_unique<HumanArcher>();
    }

    std::unique_ptr<Mage> createMage() override {
        return std::make_unique<HumanMage>();
    }
};

class ElfFactory : public AbstractFactory {
public:
    std::unique_ptr<Soldier> createSoldier() override {
        return std::make_unique<ElfSoldier>();
    }

    std::unique_ptr<Archer> createArcher() override {
        return std::make_unique<ElfArcher>();
    }

    std::unique_ptr<Mage> createMage() override {
        return std::make_unique<ElfMage>();
    }
};

// Concrete unit classes for each faction
class HumanSoldier : public Soldier {};
class HumanArcher : public Archer {};
class HumanMage : public Mage {};

class ElfSoldier : public Soldier {};
class ElfArcher : public Archer {};
class ElfMage : public Mage {};

int main() {
    AbstractFactory* factory1 = new HumanFactory();
    AbstractFactory* factory2 = new ElfFactory();

    std::unique_ptr<Soldier> humanSoldier = factory1->createSoldier();
    std::unique_ptr<Archer> humanArcher = factory1->createArcher();
    std::unique_ptr<Mage> humanMage = factory1->createMage();

    std::unique_ptr<Soldier> elfSoldier = factory2->createSoldier();
    std::unique_ptr<Archer> elfArcher = factory2->createArcher();
    std::unique_ptr<Mage> elfMage = factory2->createMage();

    humanSoldier->attack(); // Output: Soldier attacks!
    humanArcher->attack(); // Output: Archer attacks!
    humanMage->attack(); // Output: Mage attacks!

    elfSoldier->attack(); // Output: Soldier attacks!
    elfArcher->attack(); // Output: Archer attacks!
    elfMage->attack(); // Output: Mage attacks!

    delete factory1;
    delete factory2;
    return 0;
}
