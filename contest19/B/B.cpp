#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>

int getDSU(int v, std::vector<int>& p) {
    return (v == p[v]) ? v : (p[v] = getDSU(p[v], p));
}

void uniteDSU(int a, int b, std::vector<int>& p) {
    a = getDSU(a, p);
    b = getDSU(b, p);
    if (rand() & 1) {
        std::swap(a, b);
    }
    if (a != b) {
        p[a] = b;
    }
}

int main() {
    srand(time(nullptr));
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, std::pair<int, int>>> g;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        std::cin >> a >> b >> w;
        g.push_back({w, {a - 1, b - 1}});
    }

    std::sort(g.begin(), g.end());
    std::vector<int> p;
    p.resize(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }

    int cost = 0;
    std::vector<std::pair<int, int>> res;

    for (int i = 0; i < m; ++i) {
        int a = g[i].second.first;
        int b = g[i].second.second;
        int w = g[i].first;
        if (getDSU(a, p) != getDSU(b, p)) {
            cost += w;
            res.push_back(g[i].second);
            uniteDSU(a, b, p);
        }
    }

    std::cout << cost << std::endl;
}