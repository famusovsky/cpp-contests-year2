#include <string>
#include <iostream>

class Vector {
public:
    explicit Vector(size_t n_size) {
        size_ = n_size;
        for (size_t i = 0; i < size_; ++i) {
            *(point_ + i) = 0;
        }
    }

    Vector(const Vector& vec) {
        size_ = vec.size_;
        for (size_t i = 0; i < size_; ++i) {
            *(point_ + i) = *(vec.point_ + i);
        }
    }

    ~Vector() {
        delete[] point_;
    }

    size_t getSize() const {
        return size_;
    }

    void insert(size_t pos, int value) {
        for (size_t i = size_; i > pos; --i) {
            *(point_ + i) = *(point_ + i - 1);
        }
        *(point_ + pos) = value;
        ++size_;
    }

    void erase(size_t pos) {
        for (size_t i = pos; i < size_ - 1; ++i) {
            *(point_ + i) = *(point_ + i + 1);
        }
        --size_;
    }

    int at(size_t pos) {
        return *(point_ + pos);
    }

    int& operator[](size_t pos) const {
        return *(point_ + pos);
    }

private:
    size_t size_;
    int* point_ = new int[2050000];
};

int64_t findSum(size_t first, size_t second, int mod, Vector vector) {
    int64_t sum = 0;
    for (; first <= second; ++first) {
        sum += vector.at(first);
    }
    sum %= mod;
    return sum > 0 ? sum : mod + sum;
}

int findXOR(size_t first, size_t second, Vector vector) {
    int x_o_r = vector.at(first++);
    for (; first <= second; ++first) {
        x_o_r ^= vector.at(first);
    }
    return x_o_r;
}

int main() {
    bool is_sum;
    int mod, num;
    std::string command;
    std::cin >> command;
    if (command == "+") {
        is_sum = true;
        std::cin >> mod;
    } else {
        is_sum = false;
    }
    std::cin >> num;
    Vector vector(num);
    for (int i = 0; i < num; ++i) {
        std::cin >> vector[i];
    }
    std::cin >> num;
    int a, b;
    for (int i = 0; i < num; ++i) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> a >> b;
            vector.insert(--a, b);
        } else if (command == "erase") {
            std::cin >> a;
            vector.erase(--a);
        } else if (command == "change") {
            std::cin >> a >> b;
            vector[--a] = b;
        } else if (command == "at") {
            std::cin >> a;
            std::cout << vector.at(--a) << '\n';
        } else if (command == "compute") {
            std::cin >> a >> b;
            if (is_sum) {
                std::cout << findSum(--a, --b, mod, vector) << '\n';
            } else {
                std::cout << findXOR(--a, --b, vector) << '\n';
            }
        } else {
            std::cout << vector.getSize() << '\n';
        }
    }
    return 0;
}