#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::cin >> s;
    std::vector<int> pi(s.size());

    for (size_t i = 1; i < s.size(); i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        pi[i] = j + (s[i] == s[j]);
    }

    for (const auto& item : pi) {
        std::cout << item << ' ';
    }
    std::cout << '\n';
    return 0;
}
