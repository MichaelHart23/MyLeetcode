#include <bits/stdc++.h>
using namespace std;

typedef unordered_map<int, vector<pair<int, int>>> Graph;  // <src, [<des, cost>...]>
// 其实如果不关心最短路径具体是什么的话，不需要记录src，只要目标点和cost就够了
typedef tuple<int, int, int> Edge;                  // <src, des, 从原点到des的累计weight>

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 这是根据我自己推导的dijkstra的思路写的，和流传在网上的标准写法不一样
        // 哈希表不用把编号从 [1,n] 转为 [0,n-1], 但速度比数组慢
        Graph graph;
        for (auto& t : times) {
            graph[t[0]].push_back({t[1], t[2]});
        }
        unordered_map<int, int> found;  // 已经找到最短路径的点集
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // <cost, des>
        found[k] = 0;
        for (auto i : graph[k]) {
            int des = i.first;
            int cost = i.second;
            pq.push({cost, des});
        }
        while (!pq.empty()) {
            int p = pq.top().second;
            int cost = pq.top().first;
            pq.pop();
            if (found.contains(p)) continue;
            found[p] = cost;
            for (auto i : graph[p]) {
                int weight = i.second;
                int des = i.first;
                pq.push({cost + weight, des});
            }
        }
        if (found.size() < n) {
            return -1;
        }
        int res = 0;
        for (auto [p, cost] : found) {
            if (cost > res) {
                res = cost;
            }
        }
        return res;

        // 数组写法
        // vector<vector<pair<int, int>>> g(n);  // 邻接表
        // for (auto& t : times) {
        //     g[t[0] - 1].emplace_back(t[1] - 1, t[2]);
        // }
        // int S = k - 1;
        // return -1;
    }
};
