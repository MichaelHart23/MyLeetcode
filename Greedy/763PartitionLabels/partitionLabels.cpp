#include <bits/stdc++.h>

using namespace std;

/**
 * 区间合并？对
 * 我统计了26个每个字符从出现区间
 * 去掉没出现的字符
 * 排序这些区间
 * 合并这些区间
 */
class Solution {
    void addToInterval(int i, pair<int, int>& p) {
        if(p.first == -1 && p.second == -1) {
            p.first = p.second = i;
            return;
        }
        if(i < p.first) {
            p.first = i;
        } else if(i > p.second) {
            p.second = i;
        }
    }
public:
    vector<int> partitionLabels(string s) {
        int size = s.size();
        vector<pair<int, int>> intervals(26, {-1, -1});
        vector<pair<int, int>> toBeMerge;
        map<int, int> state;
        for(int i = 0; i < size; i++) {
            int index = s[i] - 'a';
            addToInterval(i, intervals[index]);
        }
        for(auto p : intervals) {
            if(p.first != -1 && p.second != -1) {
                toBeMerge.push_back(p);
            }
        }
        auto cmp = [&](pair<int, int>& a, pair<int, int>& b) {
            return a.first < b.first;
        };
        sort(toBeMerge.begin(), toBeMerge.end(), cmp); 
        size = toBeMerge.size();
        vector<pair<int, int>> res;
        for(int i = 0; i < size; i++) {
            if(!res.empty() && res.back().second >= toBeMerge[i].first) {
                res.back().second = max(res.back().second, toBeMerge[i].second);
            } else {
                res.push_back(toBeMerge[i]);
            }
        }
        vector<int> ans;
        for(auto [x, y] : res) {
            ans.push_back(y - x + 1);
        } 
        return ans;
    }
};

/**
 * 切分区间的逻辑可以看作：
 * 从某处开始的区间，区间内的所有字母最后出现的位置中，最右边的那个位置
 */
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int size = s.size();
        int last[26]; //每个字母出现的最后位置
        vector<int> ans;
        for(int i = 0; i < size; i++) {
            last[s[i] - 'a'] = i;
        }
        int start = 0, end = 0;
        for(int i =0; i < size; i++) {
            end = max(end, last[s[i] - 'a']);
            if(i == end) { //到达区间内的所有字母最后出现的位置中，最右边的那个位置
                ans.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return ans;
    }
};
