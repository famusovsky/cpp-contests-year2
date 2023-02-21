#include <stack>
#include <algorithm>

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
    std::stack<std::pair<int, int>> first_stack_, second_stack_;
};