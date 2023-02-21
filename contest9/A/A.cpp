#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int *arr = new int[n];
    int i = 0;
    for (i = 0; i < n; i++) {
        std::cin >> arr[i];
        if (((i - 1) / 2 >= 0 && (i - 1) % 2 == 0 && arr[i] > arr[(i - 1) / 2]) ||
            ((i - 2) / 2 >= 0 && (i - 2) % 2 == 0 && arr[i] > arr[(i - 2) / 2])) {
            break;
        }
    }
    std::cout << i - 1;
    delete[] arr;
    return 0;
}