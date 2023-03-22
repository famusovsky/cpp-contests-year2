#include <string>
#include <vector>
#include <iostream>

int distanceDamLev(const std::string& a, const std::string& b) {
    int m = a.size(), n = b.size();
    std::vector<std::vector<int>> d(m + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= m; i++) {
        d[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        d[0][j] = j;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                d[i][j] = std::min(d[i - 1][j], std::min(d[i][j - 1], d[i - 1][j - 1])) + 1;
            }
            if (i > 1 && j > 1 && a[i - 1] == b[j - 2] && a[i - 2] == b[j - 1]) {
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + 1);
            }
        }
    }
    return d[m][n];
}

int main() {
    int n;
    std::cin >> n;
    std::string a, b;
    for (int i = 0; i < n; ++i) {
        std::cin >> a >> b;
        std::cout << distanceDamLev(a, b) << ' ';
    }
    return 0;
}