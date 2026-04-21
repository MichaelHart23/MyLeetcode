#include <bits/stdc++.h>

using namespace std;

/**
 * 用不着dp啊，直接数学就解决了
 * 一共要走 m - 1 + n - 1步，在其中选择m - 1步往右走，其余的都往下走
 * C (m - 1)(m + n - 2)
 * 
 * 先算分子和分母然后除会溢出，只能边乘边除
 * 那会不会出小数呢？
 * 答案是不会，但我不知道怎么证
 */
class Solution {
    //组合数计算：从m个数中选n个数的选法
    long long comb(int m, int n) {
        n = min(n, m - n);
        long long res = 1;
        for(long long i = 0; i < n; i++) {
            res *= m - i;
            res /= i + 1;
        }
        return res;
    }
public:
    int uniquePaths(int m, int n) {
        return comb(m + n - 2, m - 1);
    }
};

/**
 * dp做法
 */
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n , 1));
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
