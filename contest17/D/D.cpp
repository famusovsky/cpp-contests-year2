#include <iostream>
#include <vector>
#include <deque>

struct Coordinate {
    int x;
    int y;

    bool operator==(const Coordinate &other) const {
        return x == other.x && y == other.y;
    }
};

void findWay(const int &from_x, const int &from_y, const int &to_x, const int &to_y,
             std::vector<std::vector<bool>> &visited, std::deque<Coordinate> &current_path,
             std::deque<Coordinate> &min_path, const std::vector<Coordinate> &steps) {
    if (from_x == to_x && from_y == to_y) {
        min_path = current_path;
        return;
    }

    for (const Coordinate &s : steps) {
        int x = from_x + s.x;
        int y = from_y + s.y;
        if (x > 0 && x < static_cast<int>(visited.size()) && y > 0 &&
            y < static_cast<int>(visited.size()) && !visited[x][y]) {
            if (min_path.empty() || current_path.size() + 1 < min_path.size()) {
                visited[x][y] = true;
                current_path.push_back({x, y});
                findWay(x, y, to_x, to_y, visited, current_path, min_path, steps);
                visited[x][y] = false;
                current_path.pop_back();
            }
        }
    }
}

void minSteps(int n, int x1, int y1, int x2, int y2) {
    std::vector<std::vector<bool>> visited(n + 1, std::vector<bool>(n + 1, false));
    std::vector<Coordinate> steps = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                                     {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    std::deque<Coordinate> current_path = {{x1, y1}};
    std::deque<Coordinate> min_path;

    visited[x1][y1] = true;
    findWay(x1, y1, x2, y2, visited, current_path, min_path, steps);

    std::cout << min_path.size() - 1 << '\n';
    for (const Coordinate &c : min_path) {
        std::cout << c.x << ' ' << c.y << '\n';
    }
}

int main() {
    int n, x1, y1, x2, y2;
    std::cin >> n >> x1 >> y1 >> x2 >> y2;
    minSteps(n, x1, y1, x2, y2);
    return 0;
}
