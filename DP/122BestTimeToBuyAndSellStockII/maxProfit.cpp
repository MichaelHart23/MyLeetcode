#include <bits/stdc++.h>

using namespace std;


/**
 * 最大化股票收益：只需要找到所有的递增区间就好了
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<pair<int, int>> pairs;
        int left = 0, right = 0;
        int i = 0;
        while(true) {
            while(i < n - 1 && prices[i] >= prices[i + 1]) {
                i++;
            }
            if(i == n - 1) break;
            left = i;
            while(i < n - 1 && prices[i] <= prices[i + 1]) {
                i++;
            }
            right = i;
            pairs.push_back({prices[left], prices[right]});
            if(i == n - 1) break;
        }
        n = pairs.size();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans += pairs[i].second - pairs[i].first;
        }
        return ans;
    }
};
