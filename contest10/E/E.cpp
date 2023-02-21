#include <cstdio>
#include <vector>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t n, m, q, input;
    scanf("%lld %lld %lld", &n, &m, &q);
    std::vector<std::vector<int64_t>> matrix(n, std::vector<int64_t>(m));
    for (int64_t i = 0; i < n; i++) {
        int64_t sum = 0;
        for (int64_t j = 0; j < m; j++) {
            scanf("%lld", &input);
            sum += input;
            matrix[i][j] = sum;
        }
    }
    int64_t x1, y1, x2, y2;
    for (int64_t i = 0; i < q; ++i) {
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        int64_t sum = 0;
        for (int64_t j = x1 - 1; j <= x2 - 1; ++j) {
            sum += matrix[j][y2 - 1] - (y1 - 1 == 0 ? 0 : matrix[j][y1 - 1 - 1]);
        }
        printf("%lld\n", sum);
        fflush(stdout);
    }
    return 0;
}
