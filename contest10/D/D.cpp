#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    char field[n][n];
    int x_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> field[i][j];
            if (field[i][j] == 'X') {
                x_count++;
            }
        }
    }
    int max_zero_count = x_count / 3;
    int zero_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (field[i][j] == 'X') {
                std::cout << 'X';
            } else if (zero_count < max_zero_count && (i == 0 || field[i - 1][j] != '0') &&
                       (i == 1 || (i > 1 && field[i - 2][j] != '0')) && (j == 0 || field[i][j - 1] != '0') &&
                       (j == 1 || (j > 1 && field[i][j - 2] != '0'))) {
                std::cout << '0';
                zero_count++;
            } else {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
    return 0;
}
