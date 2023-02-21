#include <cstdlib>
#include <iostream>
#include <climits>

struct Building {
    int id;
    int distance;
};

void countingSort10(Building arr[], int n, int exp) {
    Building *b = new Building[n];
    int *c = new int[10];
    for (int i = 0; i < 10; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        c[(arr[i].distance / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i) {
        c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        b[c[(arr[i].distance / exp) % 10] - 1] = arr[i];
        --c[(arr[i].distance / exp) % 10];
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = b[i];
    }
    delete[] b;
    delete[] c;
}

void radixSort10(Building arr[], int n, int max) {
    int exp = 1;
    while (max / exp > 0) {
        countingSort10(arr, n, exp);
        exp *= 10;
    }
}

int main() {
    int n, m, a, max_v = INT_MIN, max_s = INT_MIN;
    std::cin >> n;
    Building *villages = new Building[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        villages[i] = {i, a};
        if (a > max_v) {
            max_v = a;
        }
    }
    std::cin >> m;
    Building *shelters = new Building[m];
    for (int i = 0; i < m; i++) {
        std::cin >> a;
        shelters[i] = {i, a};
        if (a > max_s) {
            max_s = a;
        }
    }
    radixSort10(villages, n, max_v);
    radixSort10(shelters, m, max_s);
    int i = 0, j = 0;
    int *res = new int[n];
    for (; i < n; ++i) {
        while (j + 1 < m && std::abs(shelters[j].distance - villages[i].distance) >
                                std::abs(shelters[j + 1].distance - villages[i].distance)) {
            ++j;
        }
        res[villages[i].id] = shelters[j].id + 1;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << res[i] << " ";
    }
    delete[] villages;
    delete[] shelters;
    delete[] res;
    return 0;
}