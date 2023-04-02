#include <iostream>
#include <string>
#include <vector>
#include <cmath>

std::string getFromHemmingCode(std::string input) {
    std::vector<char> vec(input.begin(), input.end());
    size_t cnt = 0;
    for (size_t i = 1; i < vec.size(); i *= 2) {
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

    int index_of_mistake = -1;

    for (size_t i = 0; i < cnt; ++i) {
        int sum = 0;
        for (size_t j = 0; j < vec.size(); ++j) {
            if (matrix[i][j] == '1' && vec[j] == '1') {
                sum += 1;
            }
        }
        index_of_mistake += (sum % 2) * std::pow(2, i);
    }

    if (index_of_mistake >= 0 && index_of_mistake < static_cast<int>(vec.size())) {
        vec[index_of_mistake] = (vec[index_of_mistake] + 1) % 2 + '0';
    }

    for (size_t i = 0; i < cnt; ++i) {
        size_t index = std::pow(2, i) - 1 - i;
        if (index < vec.size()) {
            vec.erase(vec.begin() + index);
        }
    }

    std::string result(vec.begin(), vec.end());
    return result;
}

int main() {
    std::string input;
    std::cin >> input;
    std::cout << getFromHemmingCode(input) << '\n';
}
