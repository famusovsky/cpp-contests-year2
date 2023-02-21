#include <iostream>
#include <deque>
#include <algorithm>

template <typename T>
class Stack {
public:
    void push(T value) {
        if (cnt_ < capacity_) {
            *(point_ + cnt_++) = value;
        } else {
            capacity_ *= 2;
            T *temp = new T[capacity_];
            size_t i = 0;
            for (; i < cnt_; ++i) {
                *(temp + i) = *(point_ + i);
            }
            *(temp + i) = value;
            delete[] point_;
            point_ = temp;
            ++cnt_;
        }
    }

    T pop() {
        if (cnt_ > 0) {
            T item = *(point_ + --cnt_);
            return item;
        } else {
            throw std::runtime_error("error");
        }
    }

    [[nodiscard]] T top() const {
        if (cnt_ > 0) {
            return *(point_ + cnt_ - 1);
        } else {
            throw std::runtime_error("error");
        }
    }

    [[nodiscard]] size_t size() const {
        return cnt_;
    }

    void clear() {
        cnt_ = 0;
        capacity_ = 1;
        delete[] point_;
        point_ = new T[capacity_];
    }

    bool empty() const {
        return cnt_ == 0;
    }

    Stack() {
        point_ = new T[capacity_];
    }

    ~Stack() {
        delete[] point_;
    }

private:
    size_t cnt_ = 0, capacity_ = 1;
    T *point_;
};

class Queue {
public:
    void push(int value) {
        if (first_stack_.empty()) {
            first_stack_.push({value, value});
        } else {
            first_stack_.push({value, std::min(value, first_stack_.top().second)});
        }
    }

    int pop() {
        if (second_stack_.empty()) {
            while (!first_stack_.empty()) {
                second_stack_.push({first_stack_.top().first,
                                    second_stack_.empty() ? first_stack_.top().first
                                                          : std::min(first_stack_.top().first,
                                                                     second_stack_.top().second)});
                first_stack_.pop();
            }
        }
        int item = second_stack_.top().first;
        second_stack_.pop();
        return item;
    }

    int min() const {
        if (first_stack_.empty()) {
            return second_stack_.top().second;
        } else if (second_stack_.empty()) {
            return first_stack_.top().second;
        } else {
            return std::min(first_stack_.top().second, second_stack_.top().second);
        }
    }

private:
    Stack<std::pair<int, int>> first_stack_, second_stack_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k, inp;
    std::cin >> n >> k;
    Queue queue;
    for (int i = 0; i < n; ++i) {
        std::cin >> inp;
        queue.push(inp);
        if (i >= k - 1) {
            std::cout << queue.min() << " ";
            queue.pop();
        }
    }
}