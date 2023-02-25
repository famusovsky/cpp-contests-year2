#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
    double start, end, weight;

    bool operator<(const Interval& other) const {
        return end < other.end;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Interval> intervals(n);
    for (int i = 0; i < n; i++) {
        std::cin >> intervals[i].start >> intervals[i].end >> intervals[i].weight;
    }
    std::sort(intervals.begin(), intervals.end());
    std::vector<double> dp(n);
    dp[0] = intervals[0].weight;
    for (int i = 1; i < n; i++) {
        double weight = intervals[i].weight;
        int j = std::upper_bound(intervals.begin(), intervals.begin() + i,
                                 Interval{0, intervals[i].start, 0}) 
                - intervals.begin() - 1;
        if (j >= 0) {
            dp[i] = std::max(dp[j] + weight, dp[i - 1]);
        } else {
            dp[i] = std::max(weight, dp[i - 1]);
        }
    }
    std::cout.precision(4);
    std::cout << std::fixed << dp[n - 1];
    return 0;
}
