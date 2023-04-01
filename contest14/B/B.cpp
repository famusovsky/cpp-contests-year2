#include <iostream>
#include <string>
#include <map>

std::string decodeEncoded(std::string encoded, std::map<std::string, char> codes_to_chars) {
    std::string current_code, decoded;
    for (const char& ch : encoded) {
        current_code += ch;
        auto it = codes_to_chars.find(current_code);
        if (it != codes_to_chars.end()) {
            decoded += codes_to_chars[current_code];
            current_code = "";
        }
    }
    return decoded;
}

int main() {
    std::map<std::string, char> codes_to_chars;
    int k, l;
    std::string input;
    std::cin >> k >> l;
    for (int i = 0; i < k; ++i) {
        char ch, tmp;
        std::string code;
        std::cin >> ch >> tmp >> code;
        codes_to_chars[code] = ch;
    }
    std::cin >> input;

    std::string decoded_input = decodeEncoded(input, codes_to_chars);
    std::cout << decoded_input << '\n';
}