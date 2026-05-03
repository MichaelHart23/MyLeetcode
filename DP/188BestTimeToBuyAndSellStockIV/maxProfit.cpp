#include <bits/stdc++.h>

using namespace std;

// 
/**
 * 当最多允许买卖k次的时候，情况就比两次（123）要复杂一些了。
 * 如果继续用分隔单调区间的做法，那问题最终会变为一个划分问题：
 * 把各个单调区间划分为k个，在所有划分法中找最大收益的那种划分
 * 我目前想不到一种低时间复杂度的做法，还是用dp吧
 * 
 * dp方法参考stock.py文件
 * 
 * 即使是dp，也可以用单调区间的方法缩小时空复杂度
 * dp的时间复杂度是O(nk), 单调区间可以把n缩小
 */
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if(n <= 1) return 0;
        vector<int> newArr;
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
            newArr.push_back(prices[left]);
            newArr.push_back(prices[right]);
            if(i == n - 1) break;
        }
        n = newArr.size();
        if(n == 0) return 0;
        if(n == 2) return newArr[1] - newArr[0];
        //dp[i][j][0/1]表示在第i + 1天第j+1次买入/卖出后的最大利润
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k, vector<int>(2, 0)));
        for(int i = 0; i < k; i++) {
            dp[0][i][0] = -newArr[0];
            dp[0][i][1] = 0;
        }
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < k; j++) {
                if(j == 0) {
                    dp[i][j][0] = max(dp[i - 1][j][0], -newArr[i]);
                    dp[i][j][1] = max(dp[i - 1][j][1], dp[i][j][0] + newArr[i]);
                } else {
                    dp[i][j][0] = max(dp[i - 1][j][0], dp[i][j - 1][1] - newArr[i]);
                    dp[i][j][1] = max(dp[i - 1][j][1], dp[i][j][0] + newArr[i]);
                }
            }
        }
        return dp[n - 1][k - 1][1];
    }
};

int main() {

}
