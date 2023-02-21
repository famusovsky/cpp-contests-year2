#include <iostream>

std::pair<int, int> find(int cnt_mul, int cnt_add, int& value) {
    if (value % 2 != 0) {
        if (value < 0) {
            value++;
        } else {
            value--;
        }
        cnt_add++;
    }
    if (value == 0) {
        return {cnt_mul, cnt_add};
    }
    value /= 2;
    return find(cnt_mul + 1, cnt_add, value);
}

//

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, x, cnt_mul = 0, cnt_add = 0;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> x;
        auto res = find(0, 0, x);
        if (res.first > cnt_mul) {
            cnt_mul = res.first;
        }
        cnt_add += res.second;
    }
    std::cout << cnt_mul + cnt_add;
}