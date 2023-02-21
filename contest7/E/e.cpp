#include <iostream>

int search(int n) {
    int l = 1, r = n;
    int m, m_1;
    std::cout << "? " << l << " " << r << std::endl;
    std::cin >> m;
    while (l < r) {
        int mid = (l + r) / 2;
        if (mid == m) {
            if (mid + 1 <= n) {
                ++mid;
            } else {
                --mid;
            }
        }
        if (mid > m) {
            std::cout << "? " << m << " " << mid << std::endl;
        } else {
            std::cout << "? " << mid << " " << m << std::endl;
        }
        std::cin >> m_1;
        if (m_1 == m) {
            if (mid > m) {
                r = mid;
            } else {
                l = mid;
            }
        } else {
            if (mid > m) {
                l = mid;
            } else {
                l = mid;
            }
        }
    }
    return l;
}

int main() {
    int n;
    std::cin >> n;
    int ans = search(n);
    std::cout << "! " << ans << std::endl;
}