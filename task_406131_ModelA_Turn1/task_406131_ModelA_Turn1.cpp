#include <vector>
#include <stdexcept>

template<class T>
class module_stack {
private:
    std::vector<T> modules_stacking;

public:
    void push_module(const T& module)
    {
        modules_stacking.push_back(module);
    }

    void pop_module()
    {
        if (is_empty())
        {
            throw std::runtime_error("Pop from an empty stack.");
        }
        modules_stacking.pop_back();
    }

    [[nodiscard]] const T& top_module() const
    {
        if (is_empty())
        {
            throw std::runtime_error("Top of an empty stack.");
        }
        return modules_stacking.back();
    }

    [[nodiscard]] bool is_empty() const
    {
        return modules_stacking.empty();
    }

    [[nodiscard]] size_t size() const
    {
        return modules_stacking.size();
    }
};

// Example usage:
int main() {
    module_stack<int> int_stack;

    int_stack.push_module(1);
    int_stack.push_module(8);
    int_stack.push_module(4);

    std::cout << "Stack size: " << int_stack.size() << std::endl;
    std::cout << "Top element: " << int_stack.top_module() << std::endl;

    while (!int_stack.is_empty()) {
        std::cout << "Pop element: " << int_stack.top_module() << std::endl;
        int_stack.pop_module();
    }

    return 0;
}
