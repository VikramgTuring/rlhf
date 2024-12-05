#include <deque>
#include <iostream>
#include <stdexcept>
#include <iterator>

template <typename T, typename Allocator = std::allocator<T>>
class CustomStack {
public:
    // Required for Standard Container: typedef for iterator
    using iterator = typename std::deque<T, Allocator>::iterator;
    using const_iterator = typename std::deque<T, Allocator>::const_iterator;

    explicit CustomStack(Allocator alloc = Allocator()) : data(alloc) {}

    // Make it a SizedContainer
    size_t size() const noexcept { return data.size(); }
    bool empty() const noexcept { return data.empty(); }

    // Push/pop elements, adhering to stack semantics
    void push(const T& value) { data.push_back(value); }
    void push(T&& value) { data.push_back(std::move(value)); }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        data.pop_back();
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data.back();
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data.back();
    }

    // Allowed by the Sequence concept, useful for iteration.
    iterator begin() { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator begin() const { return data.begin(); }
    const_iterator end() const { return data.end(); }
    const_iterator cbegin() const { return data.cbegin(); }
    const_iterator cend() const { return data.cend(); }

private:
    std::deque<T, Allocator> data;
};

