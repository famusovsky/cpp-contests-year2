#include <iostream>
#include <string>

int maxSub(const std::string& a, const std::string& b, size_t i, size_t j, int** matrix) {
    if (a.length() == i || b.length() == j) {
        return 0;
    }
    if (matrix[i][j] != -1) {
        return matrix[i][j];
    }
    if (a[i] == b[j]) {
        matrix[i][j] = 1 + maxSub(a, b, i + 1, j + 1, matrix);
        return matrix[i][j];
    }
    matrix[i][j] = std::max(maxSub(a, b, i + 1, j, matrix), maxSub(a, b, i, j + 1, matrix));
    return matrix[i][j];
}

int main() {
    std::string inp_a, inp_b;
    std::cin >> inp_a >> inp_b;
    int** matrix = new int*[inp_a.length()];
    for (size_t i = 0; i < inp_a.length(); ++i) {
        matrix[i] = new int[inp_b.length()];
        for (size_t j = 0; j < inp_b.length(); ++j) {
            matrix[i][j] = -1;
        }
    }
    std::cout << maxSub(inp_a, inp_b, 0, 0, matrix);
    for (size_t i = 0; i < inp_a.length(); ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
