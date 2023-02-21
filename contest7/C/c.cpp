#include <iostream>
#include <iomanip>
#include <cmath>

double realBinarySearch(double left, double right, double c, double precision) {
    while (fabs(right - left) > precision) {
        double mid = (left + right) / 2;
        double res = mid * mid + sqrt(mid) - c;

        if (res > 0) {
            right = mid;
        } else {
            left = mid;
        }
    }

    return (left + right) / 2;
}

int main() {
    double c;
    std::cin >> c;
    std::cout << std::setprecision(6) << std::fixed << realBinarySearch(0, c, c, 0.000001);
    return 0;
}
