#include <iostream>

int leftBinSearch(int *arr, int n, int key) {
    int l = 0, r = n - 1, res = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == key) {
            res = mid;
            r = mid - 1;
        } else if (arr[mid] < key) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

int rightBinSearch(int *arr, int n, int key) {
    int l = 0, r = n - 1, res = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid] == key) {
            res = mid;
            l = mid + 1;
        } else if (arr[mid] < key) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

int main() {
    int n, m, cur;
    std::cin >> n >> m;
    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> cur;
        int l = leftBinSearch(a, n, cur);
        int r = rightBinSearch(a, n, cur);
        if (l == n) {
            std::cout << 0 << '\n';
        } else {
            std::cout << l + 1 << ' ' << r + 1 << '\n';
        }
    }
    delete[] a;
    return 0;
}
