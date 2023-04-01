#include <cstddef>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

std::map<char, std::string> getEncodings(const std::string& input) {
    std::map<char, int> m_counts;
    for (char ch : input) {
        if (m_counts.find(ch) != m_counts.end()) {
            m_counts[ch]++;
        } else {
            m_counts[ch] = 1;
        }
    }

    std::vector<std::pair<char, int> > v(m_counts.begin(), m_counts.end());
    std::sort(v.begin(), v.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
        return a.second > b.second;
    });

    std::map<char, std::string> m_codes;
    for (size_t i = 0; i < v.size(); ++i) {
        m_codes[v[i].first] = "";
        for (size_t j = 0; j < i; ++j) {
            m_codes[v[i].first] += "1";
        }
        if (1 == v.size() || i + 1 != v.size()) {
            m_codes[v[i].first] += "0";
        }
    }
    return m_codes;
}

int main() {
    std::string input;
    std::cin >> input;

    std::map<char, std::string> m_codes = getEncodings(input);
    std::string encoded_input;
    for (auto& ch : input) {
        encoded_input += m_codes[ch];
    }

    std::cout << m_codes.size() << ' ' << encoded_input.size() << '\n';
    for (auto& pair : m_codes) {
        std::cout << pair.first << ": ";
        for (const char& ch : pair.second) {
            std::cout << ch - '0';
        }
        std::cout << '\n';
    }
    for (const char& ch : encoded_input) {
        std::cout << ch - '0';
    }
    std::cout << "\n\n";
    return 0;
}
