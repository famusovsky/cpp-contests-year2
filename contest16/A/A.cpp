#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<int> encodeLZW(const std::string &line, std::map<std::string, int> &map) {
    char current = '\0';
    for (int i = 0; i < 128; ++i) {
        std::string s;
        s += current++;
        map[s] = i;
    }

    std::vector<int> result;
    std::string current_line;
    for (size_t i = 0; i < line.length(); ++i) {
        current_line += line[i];
        if (map.count(current_line) == 0) {
            result.push_back(map[current_line.substr(0, current_line.length() - 1)]);
            map[current_line] = map.size();
            current_line = line[i];
        }
    }
    result.push_back(map[current_line]);

    return result;
}

std::string decodeLZW(const std::vector<int> &line, const std::map<std::string, int> &map) {
    std::string result;

    std::map<int, std::string> reverse_map;
    for (std::pair<std::string, int> p : map) {
        reverse_map[p.second] = p.first;
    }

    for (int item : line) {
        result += reverse_map.at(item);
    }

    return result;
}

int main() {
    std::string input;
    std::getline(std::cin, input);

    std::map<std::string, int> map;
    std::vector<int> result = encodeLZW(input, map);

    std::cout << result.size() << '\n';
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << ' ';
    }
    std::cout << '\n';

    // std::cout << decodeLZW(result, map) << '\n';
    return 0;
}