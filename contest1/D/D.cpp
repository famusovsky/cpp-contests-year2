#include <deque>
#include <string>
#include <algorithm>
#include <iostream>

std::deque<int32_t> inputDeque() {
    std::deque<int32_t> deque;
    std::string inp;
    std::cin >> inp;
    for (auto ch : inp) {
        deque.push_front(ch - '0');
    }
    return deque;
}

void print(const std::deque<int32_t>& deque) {
    bool first_zeroes = true;
    for (auto it = deque.rbegin(); it != deque.rend(); ++it) {
        if (first_zeroes) {
            if (*it != 0) {
                first_zeroes = false;
                std::cout << *it;
            }
        } else {
            std::cout << *it;
        }
    }
    if (first_zeroes) {
        std::cout << 0;
    }
}

void normalise(std::deque<int32_t>& deque) {
    int32_t cur;
    for (size_t i = 0; i < deque.size(); ++i) {
        if (deque[i] > 9) {
            cur = deque[i];
            deque[i] = cur % 10;
            if (i + 1 < deque.size()) {
                deque[i + 1] += cur / 10;
            } else {
                deque.push_back(cur / 10);
            }
        } else if (deque[i] < 0) {
            deque[i] += 10;
            deque[i + 1] -= 1;
        }
    }
}

std::deque<int32_t> mult(const std::deque<int32_t>& fi, const std::deque<int32_t>& sec) {
    std::deque<int32_t> res;
    int32_t cur;
    for (size_t i = 0; i < sec.size(); ++i) {
        for (size_t j = 0; j < fi.size(); ++j) {
            cur = fi[j] * sec[i];
            if (res.size() > j + i) {
                res[j + i] += cur;
            } else {
                res.push_back(cur);
            }
        }
    }
    normalise(res);
    return res;
}

void equelise(std::deque<int32_t>& fi, std::deque<int32_t>& sec, size_t& size) {
    if (size % 2 != 0) {
        size++;
    }
    while (fi.size() != size) {
        fi.push_back(0);
    }
    while (sec.size() != size) {
        sec.push_back(0);
    }
}

std::deque<int32_t> sum(const std::deque<int32_t>& fi, const std::deque<int32_t>& sec) {
    std::deque<int32_t> res = fi;
    for (size_t i = 0; i < sec.size(); ++i) {
        res[i] += sec[i];
    }
    normalise(res);
    return res;
}

std::deque<int32_t> dif(const std::deque<int32_t>& fi, const std::deque<int32_t>& sec) {
    std::deque<int32_t> res = fi;
    for (size_t i = 0; i < sec.size(); ++i) {
        res[i] -= sec[i];
    }
    // print(res);
    // std::cout << ' ';
    normalise(res);
    return res;
}

std::deque<int32_t> karatsubaMult(std::deque<int32_t>& fi, std::deque<int32_t>& sec) {
    size_t size = std::max(fi.size(), sec.size());
    if (size <= 150) {
        return mult(fi, sec);
    }
    std::deque<int32_t> res;
    equelise(fi, sec, size);
    //
    size_t degree = size / 2;
    std::deque<int32_t> b(fi.begin(), fi.begin() + degree), a(fi.begin() + degree, fi.end()),
        d(sec.begin(), sec.begin() + degree), c(sec.begin() + degree, sec.end()),
        ac = karatsubaMult(a, c), bd = karatsubaMult(b, d), a_plus_b = sum(a, b),
        c_plus_d = sum(c, d), ab_cd = karatsubaMult(a_plus_b, c_plus_d);
    ab_cd = dif(ab_cd, ac);
    ab_cd = dif(ab_cd, bd);
    for (size_t i = 0; i < size; ++i) {
        ac.push_front(0);
    }
    for (size_t i = 0; i < degree; ++i) {
        ab_cd.push_front(0);
    }
    res = sum(ab_cd, bd);
    res = sum(ac, res);
    //
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::deque<int32_t> first = inputDeque(), second = inputDeque(), res;
    /*print(first);
    std::cout << ' ' << first.size();
    std::cout << '\n';
    print(second);
    std::cout << ' ' << second.size();
    std::cout << '\n';*/
    res = karatsubaMult(first, second);
    print(res);
}