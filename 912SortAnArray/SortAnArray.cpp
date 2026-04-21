#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    //迭代写法快排 + 三路分区 + 随机选取pivot
    void quickSort(vector<int>& v) {
        int left = 0, right = v.size() - 1;
        deque<pair<int, int>> dq;  // 一组l r
        dq.push_back({left, right});
        while (!dq.empty()) {
            auto [l, r] = dq.back();
            dq.pop_back();
            if (l >= r) continue;
            // 保存当前子数组的边界
            int ll = l;
            int rr = r;
            int pivot = v[l + rand() % (r - l + 1)];  // 随机选择
            int i = l;
            //[left, l):小于pivot； [l, r]：等于pivot； (r, right]：大于pivot
            while (i <= r) {
                if (v[i] < pivot) {
                    swap(v[i], v[l]);
                    i++;
                    l++;
                } else if (v[i] > pivot) {
                    swap(v[i], v[r]);
                    r--;
                } else
                    i++;
            }
            dq.push_back({ll, l - 1});
            dq.push_back({r + 1, rr});
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums);
        return nums;
    }
};