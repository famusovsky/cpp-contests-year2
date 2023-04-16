#include <iostream>
#include <vector>
#include <string>

std::vector<int> getPrefixFunc(const std::string& s) {
    std::vector<int> pi(s.size());

    for (size_t i = 1; i < s.size(); i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        pi[i] = j + (s[i] == s[j]);
    }

    return pi;
}

int main() {
    std::string input;
    std::cin >> input;
    std::vector<int> pi = getPrefixFunc(input);

    std::cout << input.size() - pi.back() << '\n';

    return 0;
}
