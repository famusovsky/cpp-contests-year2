#include <iostream>
#include <vector>

int main() {
    int all_count = 0;
    int n, inp, left, right;
    std::vector<std::pair<int, int>> vec = {{0, 0}};
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> inp;
        vec.emplace_back(all_count, 0);
        if (inp == 0) {
            ++all_count;
        }
    }
    vec.emplace_back(all_count, 0);
    for (int i = 1; i <= n; ++i) {
        vec[i].second = all_count - vec[i + 1].first;
    }
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> left >> right;
        std::cout << all_count - vec[left].first - vec[right].second << ' ';
    }
    return 0;
}
