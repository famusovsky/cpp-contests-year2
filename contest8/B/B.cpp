#include <climits>
#include <iostream>

void countingSort10(int64_t arr[], int64_t n, int64_t exp) {
    int64_t *b = new int64_t[n];
    int64_t *c = new int64_t[10];
    for (int i = 0; i < 10; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        c[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i) {
        c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        b[n - c[(arr[i] / exp) % 10]] = arr[i];
        c[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = b[i];
    }
    delete[] b;
    delete[] c;
}

void radixSort10(int64_t arr[], int64_t n, int64_t max) {
    int64_t exp = 1;
    while (max / exp > 0) {
        countingSort10(arr, n, exp);
        exp *= 10;
    }
}

int main() {
    int n;
    std::cin >> n;
    int64_t *arr = new int64_t[n];
    int64_t min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        arr[i] -= min;
    }
    radixSort10(arr, n, max);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] + min << " ";
    }
    delete[] arr;
    return 0;
}
