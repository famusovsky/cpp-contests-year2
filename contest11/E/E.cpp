#include <climits>
#include <iostream>
#include <vector>

int main() {
    int l, n;
    std::cin >> l >> n;
    std::vector<int> c(n + 2);
    c[0] = 0;
    c[n + 1] = l;
    for (int i = 1; i <= n; i++) {
        std::cin >> c[i];
    }
    std::vector<std::vector<int>> dp(n + 2, std::vector<int>(n + 2, 0));
    for (int len = 2; len <= n + 1; len++) {
        for (int i = 0; i + len <= n + 1; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;
            for (int k = i + 1; k < j; k++) {
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j] + c[j] - c[i]);
            }
        }
    }
    std::cout << dp[0][n + 1];
    return 0;
}
