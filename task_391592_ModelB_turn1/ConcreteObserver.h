class ConcreteObserver : public Observer {

public:

    explicit ConcreteObserver(RefactoredComponent& observable) : observable(observable) {

        observable.attach(std::make_unique<ConcreteObserver>(*this));

    }


    ~ConcreteObserver() {

        observable.detach(this);  // Remove observer to prevent dangling pointers

    }


    void update() override {

        std::cout << "Refactored event handled." << std::endl;

    }


private:

    RefactoredComponent& observable;

};


// Usage of RefactoredComponent

int main() {

    RefactoredComponent refactoredComp;
