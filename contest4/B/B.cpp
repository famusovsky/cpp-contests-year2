#include <iostream>
#include <cmath>

int maxPrime(int n) {
    int max_prime = 1;
    while (n % 2 == 0) {
        max_prime = 2;
        n /= 2;
    }
    for (int i = 3; i <= std::sqrt(n); i += 2) {
        while (n % i == 0) {
            max_prime = i;
            n /= i;
        }
    }
    if (n > 2) {
        max_prime = n;
    }
    return max_prime;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    int g_c_d, a, b;
    std::cin >> a >> b;
    g_c_d = gcd(a, b);
    a = maxPrime(a / g_c_d);
    b = maxPrime(b / g_c_d);
    std::cout << g_c_d * std::max(a, b);
}
