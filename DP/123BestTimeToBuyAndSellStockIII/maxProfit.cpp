#include <bits/stdc++.h>

using namespace std;

void printPairs(vector<pair<int, int>>& p) {
    for(auto [x, y] : p) {
        cout << x << ", " << y << endl;
    }
}

/**
 * 我敏锐的察觉到，只有单调递增区间才和Max Profit有关系，于是我先找出了所有的递增区间，按照其
 * 在prices数组中的前后位置记录区间左右断点元素，接下来只需要在这几个区间里选就可以了
 * 
 * 接下来我意识到，要以O(n)的时间复杂度解决，必须整前后缀，但我没想好怎么整前后缀，最终还是O(n^2)的时间
 * 复杂度解决的，最终超时了
 */
class Solution1 {
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
        if(n == 0) return 0;
        if(n == 1) return pairs[0].second - pairs[0].first;
        printPairs(pairs);
        vector<int> preMin(n, 0);
        preMin[0] = pairs[0].first;
        for(i = 1; i < n; i++) {
            preMin[i] = min(preMin[i - 1], pairs[i].first);
        }
        vector<int> postMax(n, 0);
        postMax[n - 1] = pairs[n - 1].second;
        for(i = n - 2; i >= 0; i--) {
            postMax[i] = max(postMax[i + 1], pairs[i].second);
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            int leftMax = pairs[i].second - preMin[i];
            int rightMax = 0;
            for(int j = i + 1; j < n; j++) {
                rightMax = max(rightMax, postMax[j] - pairs[j].first);
            }
            ans = max(ans, leftMax + rightMax);
        }
        return ans;
    }
};

/**
 * 还是先找出所有单调递增区间，然后正确的设计前后缀，以O(n)的时间复杂度解决
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
        if(n == 0) return 0;
        if(n == 1) return pairs[0].second - pairs[0].first;
        // pre[i]表示在[0, i]区间内一次买入卖出的最大利润
        vector<int> pre(n, 0);
        pre[0] = pairs[0].second - pairs[0].first;
        int curMin = pairs[0].first;
        for(i = 1; i < n; i++) {
            curMin = min(curMin, pairs[i].first);
            pre[i] = max(pairs[i].second - curMin, pre[i - 1]);
        }
        // post[i]表示在 (i, n - 1] 区间内一次买入卖出的最大利润
        vector<int> post(n, 0);
        post[n - 1] = 0;
        post[n - 2] = pairs[n-1].second - pairs[n-1].first;
        int curMax = pairs[n - 1].second;
        for(i = n - 3; i >= 0; i--) {
            curMax = max(curMax, pairs[i + 1].second);
            post[i] = max(post[i + 1], curMax - pairs[i + 1].first);
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            ans = max(ans, pre[i] + post[i]);
        }
        return ans;
    }
};

int main() {
    //vector<int> p = {3, 3, 5, 0, 0, 3, 1, 4};
    vector<int> p = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    Solution s;
    cout << s.maxProfit(p) << endl;
}
