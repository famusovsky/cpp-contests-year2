#include <iostream>
#include <vector>
#include <iomanip>

double findMedian(const std::vector<int> &first, const std::vector<int> &second) {
    size_t fir = 0, sec = 0, cnt = 0;
    int last = 0, cur = 0;
    bool is_first_empty = false, is_second_empty = false;
    for (size_t i = 0; i < first.size() + second.size(); ++i) {
        if (!is_first_empty && first[fir] <= second[sec] || is_second_empty) {
            ++cnt;
            last = cur;
            cur = first[fir++];
            if (fir == first.size()) {
                is_first_empty = true;
            }
        } else {
            ++cnt;
            last = cur;
            cur = second[sec++];
            if (sec == second.size()) {
                is_second_empty = true;
            }
        }
        if (cnt == first.size() + 1) {
            return (cur + last) / 2.0;
        }
    }
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, inp;
    std::cin >> n >> m;
    std::vector<std::vector<int>> vector;
    for (int i = 0; i < n; ++i) {
        vector.emplace_back();
        for (int j = 0; j < m; ++j) {
            std::cin >> inp;
            vector[i].push_back(inp);
        }
    }
    std::cout << std::fixed << std::setprecision(5);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::cout << findMedian(vector[i], vector[j]) << '\n';
        }
    }
}
