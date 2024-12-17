class RefactoredComponent : public Observable {

public:

    void notifyEvent() {

        notifyAll();

    }

};

