class Observable {

public:

    void attach(std::unique_ptr<Observer> observer) {

        observers.push_back(std::move(observer));

    }


    void notifyAll() {

        for (auto& observer : observers) {

            observer->update();

        }

    }


    void detach(Observer* observer) {

        observers.erase(std::remove_if(observers.begin(), observers.end(), [observer](const auto& ptr) {

            return ptr.get() == observer;

        }), observers.end());

    }


private:

    std::vector<std::unique_ptr<Observer>> observers;

};
