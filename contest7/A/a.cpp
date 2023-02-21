#include <iostream>

int main() {
    int max = 99, max_2 = 98, cur;
    while (std::cin >> cur) {
        if (cur == 0) {
            break;
        }
        if (cur >= 100 && cur <= 150) {
            if (cur > max) {
                max_2 = max;
                max = cur;
            } else if (cur > max_2) {
                max_2 = cur;
            }
        }
    }
    std::cout << max << '\n' << max_2;
    return 0;
}