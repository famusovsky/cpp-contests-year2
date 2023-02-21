#include <iostream>

class Stack {
public:
    void push(int value) {
        if (cnt_ < capacity_) {
            *(point_ + cnt_++) = value;
        } else {
            capacity_ *= 2;
            int *temp = new int[capacity_];
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

    int pop() {
        if (cnt_ > 0) {
            int item = *(point_ + --cnt_);
            return item;
        } else {
            throw std::runtime_error("error");
        }
    }

    [[nodiscard]] int back() const {
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
        point_ = new int[capacity_];
    }

    Stack() {
        point_ = new int[capacity_];
    }

    ~Stack() {
        delete[] point_;
    }

private:
    size_t cnt_ = 0, capacity_ = 1;
    int *point_;
};