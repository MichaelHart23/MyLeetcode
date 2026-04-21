#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
        vector<vector<int>> res;
        int left = intervals[0][0], right = intervals[0][1], n = intervals.size();
        for (int i = 1; i < n; i++) {
            if (right < intervals[i][0]) {
                res.push_back({left, right});
                left = intervals[i][0];
                right = intervals[i][1];
            } else if (right <= intervals[i][1]) {
                right = intervals[i][1];
            }
        }
        res.push_back({left, right});
        return res;
    }
};