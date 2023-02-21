#include <iostream>

int main() {
    int n, k;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    std::cin >> k;
    int input;
    for (int i = 0; i < k; ++i) {
        std::cin >> input;
        arr[input - 1]--;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << (arr[i] < 0 ? "yes" : "no") << "\n";
    }
    delete[] arr;
}