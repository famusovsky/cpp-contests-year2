#include <iostream>

int main() {
    int n, m, inp, max = 0;
    std::cin >> n >> m;
    int horizontal_sum = 0;
    int *vertical_sum = new int[m];
    for (int i = 0; i < m; i++) {
        vertical_sum[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        horizontal_sum = 0;
        for (int j = 0; j < m; j++) {
            std::cin >> inp;
            if (inp != 0) {
                horizontal_sum++;
                vertical_sum[j]++;
                int min_sum = std::min(horizontal_sum, vertical_sum[j]);
                for (int k = j; k >= j - min_sum + 1; k--) {
                    if (vertical_sum[k] < min_sum) {
                        min_sum = vertical_sum[k];
                    }
                }
                max = std::max(max, min_sum);
            } else {
                horizontal_sum = 0;
                vertical_sum[j] = 0;
            }
        }
    }
    std::cout << max << std::endl;
    delete[] vertical_sum;
    return 0;
}
