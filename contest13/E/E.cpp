#include <string>
#include <vector>
#include <iostream>

bool check(const std::string &str1, const std::string &str2, const int &max) {
    std::string s;
    std::string t;

    if (str1.length() > str2.length()) {
        s = str1;
        t = str2;
    } else {
        s = str2;
        t = str1;
    }

    if (static_cast<int>(s.length() - static_cast<int>(t.length())) > max) {
        return false;
    }

    std::vector<std::vector<int>> d(s.length() + 1, std::vector<int>(t.length() + 1));
    for (size_t i = 0; i <= s.length(); ++i) {
        d[i][0] = i;
    }
    for (size_t i = 0; i <= t.length(); ++i) {
        d[0][i] = i;
    }

    for (size_t j = 1; j <= t.length(); ++j) {
        bool is_false = true;

        for (size_t i = 1; i <= s.length(); ++i) {
            if (s[i - 1] == t[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                d[i][j] = std::min(d[i - 1][j] + 1, std::min(d[i][j - 1] + 1, d[i - 1][j - 1] + 1));
            }

            if (static_cast<int>(i) >= static_cast<int>(s.length()) - static_cast<int>(t.length()) +
                                           static_cast<int>(j) &&
                d[i][j] <= max) {
                is_false = false;
            }
        }

        if (is_false) {
            return false;
        }
    }

    return d[s.length()][t.length()] <= max;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::string> commands(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> commands[i];
    }
    int d, q;
    std::cin >> d >> q;
    std::string input;
    for (int i = 0; i < q; ++i) {
        std::cin >> input;
        int res = 0;
        for (int j = 0; j < n; ++j) {
            if (check(input, commands[j], d)) {
                ++res;
            }
        }
        std::cout << res << '\n';
    }
    return 0;
}
