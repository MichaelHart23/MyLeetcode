#include <bits/stdc++.h>
#include <optional>

using namespace std;

/**
 * 20260711初做，之前做的都是并集类的合并区间题目，这道题是交集
 */
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() < 2) {
            return points.size();
        }
        std::sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        int res = 0;
        int n = points.size();
        auto intersection = [](vector<int>& left, vector<int>& right) -> std::optional<vector<int>> {
            if (left[1] >= right[0]) {
                vector<int> res = {left[0], min(right[1], left[1])};
                return res;
            }
            return std::nullopt;
        };
        vector<int> interval = points[0];
        int i = 1;
        std::optional<vector<int>> a;
        while (i < n) {
            a = intersection(interval, points[i]);
            if (a == std::nullopt) {
                interval = points[i];
                res++;
            } else {
                interval = *a;
            }
            i++;
        }
        return res + 1;
    }
};