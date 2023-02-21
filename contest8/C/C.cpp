#include <climits>
#include <iostream>

struct Drone {
    int64_t id;
    int64_t power;
};

void countingSort10(Drone arr[], int64_t n, int64_t exp) {
    Drone *b = new Drone[n];
    int64_t *c = new int64_t[10];
    for (int i = 0; i < 10; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        c[(arr[i].power / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i) {
        c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        b[c[(arr[i].power / exp) % 10] - 1] = arr[i];
        --c[(arr[i].power / exp) % 10];
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = b[i];
    }
    delete[] b;
    delete[] c;
}

void radixSort10(Drone arr[], int64_t n, int64_t max) {
    int64_t exp = 1;
    while (max / exp > 0) {
        countingSort10(arr, n, exp);
        exp *= 10;
    }
}

int main() {
    int n;
    std::cin >> n;
    int64_t a, b, max = INT_MIN;
    Drone *arr = new Drone[n];
    for (int i = n - 1; i >= 0; --i) {
        std::cin >> a >> b;
        if (b > max) {
            max = b;
        }
        arr[i] = {a, b};
    }
    radixSort10(arr, n, max);
    for (int i = n - 1; i >= 0; i--) {
        std::cout << arr[i].id << '\t' << arr[i].power << '\n';
    }
    delete[] arr;
    return 0;
}
