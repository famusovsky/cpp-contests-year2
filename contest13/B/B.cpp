#include <string>
#include <vector>
#include <iostream>

int lev(std::string s, std::string t) {
    std::vector<std::vector<int>> d(s.length() + 1, std::vector<int>(t.length() + 1));
    for (size_t i = 0; i <= s.length(); ++i) {
        d[i][0] = i;
    }
    for (size_t i = 0; i <= t.length(); ++i) {
        d[0][i] = i;
    }

    for (size_t j = 1; j <= t.length(); ++j) {
        for (size_t i = 1; i <= s.length(); ++i) {
            if (s[i - 1] == t[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                d[i][j] = std::min(d[i - 1][j] + 1, std::min(d[i][j - 1] + 1, d[i - 1][j - 1] + 1));
            }
        }
    }

    return d[s.length()][t.length()];
}

int main() {
    std::string a, b;
    std::cin >> a >> b;
    std::cout << lev(a, b);
    return 0;
}