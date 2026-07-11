#include <bits/stdc++.h>

using namespace std;

/**
 * 先把完全在newInterval之前的区间加入res，之后找到第一个不完全在newInterval之前的，判断它们有没有交叠
 * 若没有，直接把newInterval和之后区间加入res，若有，merge之后把对应的区间加入res
 */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        int i = 0;
        vector<vector<int>> res;
        bool hasMerge = false;
        while (i < n) {
            if (hasMerge) {
                res.push_back(std::move(intervals[i]));
                i++;
                continue;
            }
            if (intervals[i][1] < newInterval[0]) {
                res.push_back(std::move(intervals[i]));
                i++;
                continue;
            }
            if (!hasMerge && intervals[i][0] > newInterval[1]) {
                res.push_back(std::move(newInterval));
                hasMerge = true;
                continue;
            }

            vector<int> interval(2);
            interval[0] = min(newInterval[0], intervals[i][0]);
            while (i < n && intervals[i][0] <= newInterval[1]) {
                interval[1] = max(intervals[i][1], newInterval[1]);
                i++;
            }
            res.push_back(std::move(interval));
            hasMerge = true;
        }
        if (!hasMerge) {
            res.push_back(std::move(newInterval));
        }
        return res;
    }
};