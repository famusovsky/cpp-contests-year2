#include <iostream>

int binSearch(int l, int r, int k, int *arr, int n) {
    int res = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += arr[i] / mid;
        }

        if (cnt >= k) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return res;
}

int main() {
    int n, k, max = -1;
    std::cin >> n >> k;
    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (a[i] > max) {
            max = a[i];
        }
    }
    int res = binSearch(0, max, k, a, n);
    std::cout << (res < 1 ? 0 : res);
    delete[] a;
    return 0;
}
