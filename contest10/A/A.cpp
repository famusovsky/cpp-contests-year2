#include <climits>
#include <iostream>

struct Event {
    int x;
    int type;

    int operator/(const int &a) const {
        return x / a;
    }
    int operator-=(const int &a) {
        x -= a;
        return x;
    }
    int operator+=(const int &a) {
        x += a;
        return x;
    }
};

template <typename T>
void countingEventSort256(T arr[], int64_t n, int64_t exp) {
    T *b = new T[n];
    int64_t *c = new int64_t[256];
    for (int i = 0; i < 256; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        c[(arr[i] / exp) % 256]++;
    }
    for (int i = 1; i < 256; ++i) {
        c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        b[c[(arr[i] / exp) % 256] - 1] = arr[i];
        --c[(arr[i] / exp) % 256];
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = b[i];
    }
    delete[] b;
    delete[] c;
}

template <typename T>
void radixSort256(T arr[], int64_t n, int64_t min, int64_t max) {
    int64_t exp = 1;
    max -= min;
    for (int i = 0; i < n; ++i) {
        arr[i] -= min;
    }
    while (max / exp > 0) {
        countingEventSort256(arr, n, exp);
        exp *= 256;
    }
    for (int i = 0; i < n; ++i) {
        arr[i] += min;
    }
}

int main() {
    int n, m, min = INT_MAX, max = INT_MIN;
    int a, b;
    std::cin >> n >> m;
    Event *events = new Event[2 * n];
    Event *points = new Event[m];
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b;
        if (a < min) {
            min = a;
        }
        if (b > max) {
            max = b;
        }
        events[2 * i] = {a, 1};
        events[2 * i + 1] = {b + 1, -1};
    }
    radixSort256(events, 2 * n, min, max);
    min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < m; i++) {
        std::cin >> a;
        if (a < min) {
            min = a;
        }
        if (a > max) {
            max = a;
        }
        points[i] = {a, i};
    }
    radixSort256(points, m, min, max);
    int count = 0;
    int i = 0;
    int *answers = new int[m];
    for (int j = 0; j < m; ++j) {
        while (i < 2 * n && events[i].x <= points[j].x) {
            count += events[i].type;
            ++i;
        }
        answers[points[j].type] = count;
    }
    for (i = 0; i < m; ++i) {
        std::cout << answers[i] << " ";
    }
    delete[] answers;
    delete[] points;
    delete[] events;
    return 0;
}