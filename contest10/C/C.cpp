#include <climits>
#include <iostream>

int main() {
    int i_res = 0, j_res = 0, result = INT_MIN;
    int min = INT_MAX, i_min = 0;
    int n, sum = 0, input;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> input;
        if (sum <= min) {
            min = sum;
            i_min = i;
        }
        sum += input;
        if (sum - min > result) {
            result = sum - min;
            i_res = i_min;
            j_res = i;
        }
    }
    std::cout << i_res << " " << j_res << '\n';
    return 0;
}