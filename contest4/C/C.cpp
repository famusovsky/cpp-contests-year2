#include <iostream>
#include <cmath>

bool findSquares(int n, int count, int *squares, int pos) {
    auto square = sqrt(n);
    if (count == 1) {
        if (square == int(square)) {
            squares[pos] = int(square);
            return true;
        }
        return false;
    }
    for (int i = 0; i < square; ++i) {
        if (findSquares(n - i * i, count - 1, squares, pos + 1)) {
            squares[pos] = i;
            return true;
        }
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k = 4;
    std::cin >> n;
    auto *squares = new int[k];
    for (int i = 0; i < k; ++i) {
        squares[i] = 0;
    }
    findSquares(n, k, squares, 0);
    bool not_only_zeros = false;
    for (int i = 0; i < k; i++) {
        if (squares[i] != 0) {
            std::cout << squares[i] << ' ';
            not_only_zeros = true;
        }
    }
    if (!not_only_zeros) {
        std::cout << 0;
    }
    delete[] squares;
    return 0;
}
