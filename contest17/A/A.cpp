#include <climits>
#include <iostream>
#include <vector>

int searchMinWay(const std::vector<std::vector<std::vector<int>>>& graph, int map_swap_count,
                 int current_map_index, int from_index) {
    int min = -1;
    for (size_t to_index = 0; to_index < graph[from_index].size(); ++to_index) {
        for (const int& map_index : graph[from_index][to_index]) {
            if (map_index != 0) {
                int new_map_swap_count = map_swap_count + (map_index != current_map_index);
                if (to_index + 1 == graph[from_index].size()) {
                    return new_map_swap_count;
                }
                int found = searchMinWay(graph, new_map_swap_count, map_index, to_index);
                if (min == -1 || (found != -1 && found < min)) {
                    min = found;
                }
            }
        }
    }
    return min;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<std::vector<int>>> graph(
        n, std::vector<std::vector<int>>(n, std::vector<int>(k, 0)));

    for (int i = 0; i < k; ++i) {
        int a, b;
        int current_map_size;
        std::cin >> current_map_size;
        for (int j = 0; j < current_map_size; ++j) {
            std::cin >> a >> b;
            graph[a - 1][b - 1].push_back(i + 1);
            graph[b - 1][a - 1].push_back(i + 1);
        }
    }

    std::cout << searchMinWay(graph, 0, 1, 0);
    return 0;
}
