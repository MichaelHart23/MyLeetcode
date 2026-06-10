#include <bits/stdc++.h>

using namespace std;

/**
 * 题目就是在一个数组中，大于等于h的元素有h个，求h的最大值
 * 我上来就排序了，但这次题目有O(n)的解法
 */
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int size = citations.size();
        for (int i = 0; i < size; i++) {
            int paper_cnt = size - i;
            if (citations[i] >= paper_cnt) {
                return paper_cnt;
            }
        }
        return 0;
    }
};

/**
 * 不排序的O(n)做法，用一个数组统计
 */
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> cnt(n + 1, 0);   // cnt[i]表示有多少篇论文被引用了i次, 大于n次的以n算
        for (int i : citations) {
            cnt[min(n, i)]++;
        }
        int num = 0;
        for (int i = n; i >= 0; i--) {
            num += cnt[i];
            if (num >= i) {
                return i;
            }
        }
        return 0;  // not reach
    }
};