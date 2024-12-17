#include <iostream>

class Button {
public:
    void click() {
        std::cout << "Button clicked!" << std::endl;
        // Direct calls to Label functionality instead of reporting event
        label.onButtonClicked();  
    }

    // Just for this legacy implementation, we are mocking the label
    class Label {
    public:
        void onButtonClicked() {
            std::cout << "Label updated because button clicked!" << std::endl;
        }
    };

    Label label;
};

int main() {
    Button button;
    button.click();

    return 0;
}
