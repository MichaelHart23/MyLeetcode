#include <bits/stdc++.h>

using namespace std;

//哈希表排序
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for(int i : nums) {
            m[i]++;
        }
        multimap<int, int, greater<int>> mm;
        for(auto [n, f] : m) {
            mm.insert({f, n});
        }
        vector<int> res;
        for(auto [f, n] : mm) {
            res.push_back(n);
            if(--k == 0) break; 
        }
        return res;
    }
};

//最大堆排序
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for(int i : nums) {
            m[i]++;
        }
        priority_queue<pair<int, int>> heap; //默认最大堆
        for(auto [n, f] : m) {
            heap.push({f, n});
        }
        vector<int> res;
        while(k--) {
            res.push_back(heap.top().second);
            heap.pop();
        }
        return res;
    }
};

//桶排序, 由于是频率，所以最大频率一定小于数组本身的大小，所以空间复杂度不大
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        int maxF = 0;
        vector<int> res;
        for(int i : nums) {
            m[i]++;
        }
        for(auto [n, f] : m) {
            maxF = max(maxF, f);
        }
        vector<vector<int>> buckets(maxF);
        for(auto[n, f] : m) {
            buckets[f - 1].push_back(n);
        }
        for(int i = maxF - 1; i >= 0; i--) {
            if(!buckets[i].empty()) {
                for(int n : buckets[i]) {
                    res.push_back(n);
                    if(--k == 0) return res;
                }
            }
        }
        return res; // won't reach
    }
};
