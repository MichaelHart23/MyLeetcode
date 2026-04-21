#include <bits/stdc++.h>

using namespace std;


/**
 * 枚举在哪一天卖出，维护这一天之前的最低价格
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int preMin = prices[0], size = prices.size(), res = 0;
        for(int i = 1; i < size; i++) {
            res = max(prices[i] - preMin, res);
            preMin = min(preMin, prices[i]);
        }
        return res;
    }
};
