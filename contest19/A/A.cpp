#include <iostream>
#include <vector>
#include <set>
#include <queue>

std::vector<int> findInitialPlacement(const int& n, const std::vector<std::pair<int, int>>& pairs) {
    std::vector<int> result(n);

    std::vector<std::set<int>> neighbors(n + 1);
    for (const auto& pair : pairs) {
        int x = pair.first;
        int y = pair.second;
        neighbors[x].insert(y);
        neighbors[y].insert(x);
    }

    int start = 1;
    for (int i = 1; i <= n; ++i) {
        if (neighbors[i].size() == 1) {
            start = i;
            break;
        }
    }

    std::vector<bool> visited(n + 1, false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;
    result[0] = start;
    int index = 1;

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int neighbor : neighbors[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                result[index++] = neighbor;
                q.push(neighbor);
                break;
            }
        }
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> pairs(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> pairs[i].first >> pairs[i].second;
    }

    std::vector<int> initial_placement = findInitialPlacement(n, pairs);

    for (int i = 0; i < n; ++i) {
        std::cout << initial_placement[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
