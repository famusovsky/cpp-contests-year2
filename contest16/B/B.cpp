#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string decodeLZW(const std::vector<int> &line) {
    std::string result;
    std::map<int, std::string> map;
    for (int i = 0; i < 128; ++i) {
        std::string s;
        s += '\0' + i;
        map[i] = s;
    }

    int current_code = line[0];
    result += map[current_code];
    char current_char = map[current_code][0];
    std::string current_line;

    for (size_t i = 1; i < line.size(); ++i) {
        int code = line[i];

        if (map.count(code) == 0) {
            current_line = map[current_code];
            current_line += current_char;
        } else {
            current_line = map[code];
        }
        result += current_line;
        current_char = current_line[0];
        map[map.size()] = map[current_code] + current_char;
        current_code = code;
    }

    return result;
}

int main() {
    int cnt;
    std::cin >> cnt;
    std::vector<int> input(cnt);

    for (int i = 0; i < cnt; ++i) {
        std::cin >> input[i];
    }

    std::cout << decodeLZW(input) << '\n';
    return 0;
}