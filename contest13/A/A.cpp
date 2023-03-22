#include <iostream>
#include <vector>
#include <string>

std::vector<int> findPrefixFunction(const std::string& str) {
    int n = str.length();
    std::vector<int> pi(n);
    pi[0] = 0;
    int k = 0;
    for (int i = 1; i < n; ++i) {
        while (k > 0 && str[k] != str[i]) {
            k = pi[k - 1];
        }
        if (str[k] == str[i]) {
            k++;
        }
        pi[i] = k;
    }
    return pi;
}

std::vector<int> findBorderFunction(const std::string& str) {
    int n = str.length();
    std::vector<int> pi = findPrefixFunction(str);
    std::vector<int> border(n);
    border[0] = 0;
    for (int i = 1; i < n; ++i) {
        if (str[pi[i]] != str[i + 1]) {
            border[i] = pi[i];
        } else {
            border[i] = border[pi[i]];
        }
    }
    return border;
}

std::vector<int> knuthMorrisPratt(const std::string& str, const std::string& substr) {
    int n = str.length();
    int m = substr.length();
    std::vector<int> result;
    if (m == 0 || n == 0) {
        return result;
    }
    std::vector<int> border = findBorderFunction(substr);
    int k = 0;
    for (int i = 1; i <= n; ++i) {
        while (k > 0 && substr[k] != str[-1 + i]) {
            k = border[-1 + k];
        }
        if (substr[k] == str[-1 + i]) {
            k++;
        }
        if (k == m) {
            result.push_back(i - m);
            k = border[-1 + k];
        }
    }
    return result;
}

int main() {
    std::string str, substr;
    std::cin >> substr >> str;
    std::vector<int> v = knuthMorrisPratt(str, substr);
    std::cout << v.size() << '\n';
    for (int item : v) {
        std::cout << item << '\n';
    }
    return 0;
}
