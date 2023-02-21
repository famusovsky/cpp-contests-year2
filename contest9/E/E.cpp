#include <iostream>
#include <vector>
#include <string>

struct TimeMoment {
    int moment;
    int start_or_end;
};

void countingSort256(TimeMoment arr[], int n, int exp) {
    TimeMoment *b = new TimeMoment[n];
    int *c = new int[256];
    for (int i = 0; i < 256; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        c[(arr[i].moment / exp) % 256]++;
    }
    for (int i = 1; i < 256; ++i) {
        c[i] += c[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        b[c[(arr[i].moment / exp) % 256] - 1] = arr[i];
        --c[(arr[i].moment / exp) % 256];
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = b[i];
    }
    delete[] b;
    delete[] c;
}

void radixSort256(TimeMoment arr[], int n, int max) {
    int exp = 1;
    while (max / exp > 0) {
        countingSort256(arr, n, exp);
        exp *= 256;
    }
}

int main() {
    int n, x, y;
    std::cin >> n;
    TimeMoment *moments = new TimeMoment[2 * n];
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        moments[2 * i] = {x, 1};
        moments[2 * i + 1] = {y, -1};
    }
    radixSort256(moments, 2 * n, 255);
    std::string input;
    std::cin >> input;
    while (input != "!") {
        std::cin >> x;
        int count = 0;
        bool found = false;
        for (int i = 0; i < 2 * n; i++) {
            if (moments[i].moment > x) {
                found = true;
                std::cout << "! " << count << std::endl;
                break;
            }
            count += moments[i].start_or_end;
        }
        if (!found) {
            std::cout << "! " << count << std::endl;
        }
        std::cin >> input;
    }
    delete[] moments;
    return 0;
}