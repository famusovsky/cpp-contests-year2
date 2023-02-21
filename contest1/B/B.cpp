#include <deque>
#include <iostream>

class Deque {
public:
    void pushBack(int value) {
        deque_.push_back(value);
    }

    void pushMiddle(int value) {
        size_t middle = deque_.size() % 2 == 0 ? deque_.size() / 2 : deque_.size() / 2 + 1;
        deque_.insert(deque_.begin() + middle, value);
    }

    int popFront() {
        int item = deque_.front();
        deque_.pop_front();
        return item;
    }

    [[nodiscard]] int front() const {
        return deque_.front();
    }

    [[nodiscard]] int back() const {
        return deque_.back();
    }

    [[nodiscard]] size_t size() const {
        return deque_.size();
    }

private:
    std::deque<int> deque_;
};