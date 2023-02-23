#include <iostream>
#include <vector>
#include <algorithm>

void way(std::vector<std::vector<int>> &matrix, int i, int j, std::vector<int> &arr,
         std::vector<int> &res) {
    if (i == 0 || j == 0) {
        return;
    }
    if (matrix[i][j] != matrix[i - 1][j]) {
        way(matrix, i - 1, j - arr[i - 1], arr, res);
        res.push_back(arr[i - 1]);
    } else {
        way(matrix, i - 1, j, arr, res);
    }
}

int main() {
    int n, w;
    std::cin >> n >> w;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::vector<std::vector<int>> matrix(n + 1, std::vector<int>(w + 1));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= w; ++j) {
            if (i == 0 || j == 0) {
                matrix[i][j] = 0;
            } else if (j - arr[i - 1] >= 0) {
                matrix[i][j] =
                    std::max(matrix[i - 1][j], matrix[i - 1][j - arr[i - 1]] + arr[i - 1]);
            } else {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }
    std::cout << matrix[n][w] << '\n';
    std::vector<int> res;
    res.reserve(n);
    way(matrix, n, w, arr, res);
    std::cout << res.size() << '\n';
    for (int i = 0; i < static_cast<int>(res.size()); ++i) {
        std::cout << res[i] << ' ';
    }
    return 0;
}