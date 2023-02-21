#include <climits>
#include <iostream>

void palindrome(int *count, int n, int k) {
    int center = -1;
    int *result = new int[n];
    int i = 0;
    for (int j = 0; j <= k; j++) {
        for (int z = 0; z < count[j] / 2; ++z) {
            result[i++] = j;
        }
        if (center == -1 && count[j] % 2 == 1) {
            center = j;
        }
    }
    for (int j = 0; j < i; ++j) {
        std::cout << static_cast<char>(result[j] + 65);
    }
    if (center != -1) {
        std::cout << static_cast<char>(center + 65);
    }
    for (int j = i - 1; j >= 0; --j) {
        std::cout << static_cast<char>(result[j] + 65);
    }
    delete[] result;
}

void getPalindrome(int *a, int n, int k) {
    int *c = new int[k + 1];
    for (int i = 0; i <= k; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i <= n - 1; ++i) {
        c[a[i]] = c[a[i]] + 1;
    }
    palindrome(c, n, k);
    delete[] c;
}

int main() {
    int n;
    char inp;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> inp;
        arr[i] = inp - 65;
    }
    getPalindrome(arr, n, 90 - 65);
    delete[] arr;
    return 0;
}
