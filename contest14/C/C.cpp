#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::string getHemmingCode(std::string input) {
    std::vector<char> vec(input.begin(), input.end());
    size_t cnt = 0;
    for (size_t i = 1; i <= vec.size(); i *= 2) {
        vec.insert(vec.begin() + i - 1, '0');
        ++cnt;
    }

    std::vector<std::vector<char> > matrix =
        std::vector<std::vector<char> >(cnt, std::vector<char>(vec.size()));
    for (size_t j = 0; j < vec.size(); ++j) {
        int tmp = j + 1;
        for (size_t i = 0; i < cnt; ++i) {
            matrix[i][j] = tmp % 2 + '0';
            tmp /= 2;
        }
    }

    for (size_t i = 0; i < cnt; ++i) {
        int sum = 0;
        for (size_t j = 0; j < vec.size(); ++j) {
            if (matrix[i][j] == '1' && vec[j] == '1') {
                sum += 1;
            }
        }
        vec[std::pow(2, i) - 1] = sum % 2 + '0';
    }

    std::string result(vec.begin(), vec.end());
    return result;
}

int main() {
    std::string input;
    std::cin >> input;
    std::cout << getHemmingCode(input);
}