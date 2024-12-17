class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void operation() {
        // Some operation
    }

private:
    Singleton() {}
};
