// LegacyCode.h
class LegacyComponent {
public:
    void addEventListener(void(*listener)()) {
        eventListeners.push_back(listener);
    }

    void notifyEvent() {
        for (auto listener : eventListeners) {
            listener();
        }
    }

private:
    std::vector<void(*)(void)> eventListeners;
};

// Usage of LegacyComponent
void legacyEventHandler() {
    std::cout << "Legacy event handled." << std::endl;
}

int main() {
    LegacyComponent legacyComp;
    legacyComp.addEventListener(legacyEventHandler);
    legacyComp.notifyEvent();  // Output: Legacy event handled.
}
