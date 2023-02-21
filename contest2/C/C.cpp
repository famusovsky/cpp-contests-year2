#include <iostream>
#include <vector>
#include <string>

bool find(const std::vector<std::pair<std::string, size_t>>& vec, const std::string& string) {
    for (const auto& pair : vec) {
        if (pair.first == string) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, cur, cnt = 0, max = 0;
    std::string line;
    std::cin >> n;
    std::vector<int> vec;
    std::vector<std::pair<std::string, size_t>> answers;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> cur;
        vec.push_back(cur);
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            cur = i - k >= 0 ? i - k : n + i - k;
            if (vec[cur] != vec[i]) {
                cnt++;
            }
            line += std::to_string(vec[cur]);
            line += ' ';
        }
        line.pop_back();
        if (max == cnt && !find(answers, line)) {
            answers.emplace_back(line, k);
        } else if (max < cnt) {
            max = cnt;
            answers.clear();
            answers.emplace_back(line, k);
        }
        cnt = 0;
        line.clear();
    }
    std::cout << max << '\n';
    for (const auto& pair : answers) {
        std::cout << pair.first << ';' << ' ' << pair.second << '\n';
    }
    return 0;
}