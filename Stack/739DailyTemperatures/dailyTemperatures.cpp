#include <bits/stdc++.h>

using namespace std;

class Solution {
  public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        deque<int> stk;
        int size = temperatures.size();
        vector<int> res(size, 0);
        auto get = [&](int i) {
            if (i < 0 || i >= size) return INT32_MAX;
            return temperatures[i];
        };
        stk.push_back(-1);  // 栈底哨兵
        int i = 0;
        while (true) {
            int top = stk.back();
            if (get(i) > get(top)) {
                res[top] = i - top;
                stk.pop_back();
            } else {
                stk.push_back(i++);
            }
            if (i >= size) break;
        }
        return res;
    }
};

class Solution {
  public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        deque<int> stk;
        int size = temperatures.size();
        vector<int> res(size, 0);
        res[size - 1] = 0;
        stk.push_back(size - 1);
        for(int i = size - 2; i >= 0; i--) {
            while(!stk.empty() && temperatures[i] >= temperatures[stk.back()]) {
                stk.pop_back();
            }
            if(stk.empty()) res[i] = 0;
            else res[i] = stk.back() - i;
            stk.push_back(i);
        }
        return res;
    }
};
