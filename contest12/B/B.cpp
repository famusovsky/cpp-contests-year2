#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(m));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i + 2 < n && j + 1 < m) {
                dp[i + 2][j + 1] += dp[i][j];
            }
            if (i + 1 < n && j + 2 < m) {
                dp[i + 1][j + 2] += dp[i][j];
            }
            if (i + 2 < n && j - 1 >= 0) {
                dp[i + 2][j - 1] += dp[i][j];
            }
            if (i + 1 < n && j - 2 >= 0) {
                dp[i + 1][j - 2] += dp[i][j];
            }
        }
    }
    std::cout << dp[n - 1][m - 1] << '\n';
    return 0;
}