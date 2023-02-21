#include <climits>
#include <iostream>

int *stableCountingSort(int *a, int n, int k) {
    int *c = new int[k + 1];
    int *b = new int[n];
    for (int i = 0; i <= k; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i <= n - 1; ++i) {
        c[a[i]] = c[a[i]] + 1;
    }
    for (int i = 1; i <= k; ++i) {
        c[i] = c[i] + c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        c[a[i]] = c[a[i]] - 1;
        b[c[a[i]]] = a[i];
    }
    delete[] c;
    return b;
}

int main() {
    int n, min = INT_MAX, max = INT_MIN;
    std::cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (a[i] > max) {
            max = a[i];
        }
        if (a[i] < min) {
            min = a[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        a[i] -= min;
    }
    int *res = stableCountingSort(a, n, max - min + 1);
    for (int i = 0; i < n; ++i) {
        std::cout << res[i] + min << " ";
    }
    delete[] a;
    delete[] res;
    return 0;
}