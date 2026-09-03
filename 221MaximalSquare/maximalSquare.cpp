#include <bits/stdc++.h>
using namespace std;

/**
 * 20260903:
 * 我没能严格数学证明三个里面取最小, 但我能根据图像大概想象出来
 * 以某个点为右下角的最大正方形, 取决于其: 左, 上, 左上 的三个点各自的正方形重合出来的那一个正方形
 */
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        int max_len = 0;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][0] == '1') {
                dp[i][0] = 1;
                max_len = 1;
            }
        }
        for (int i = 0; i < cols; i++) {
            if (matrix[0][i] == '1') {
                dp[0][i] = 1;
                max_len = 1;
            }
        }
        for (int r = 1; r < rows; r++) {
            for (int c = 1; c < cols; c++) {
                if (matrix[r][c] == '0') {
                    dp[r][c] = 0;
                    continue;
                }
                int temp = min(dp[r-1][c], dp[r-1][c-1]);
                temp = min(temp, dp[r][c-1]);
                dp[r][c] = temp + 1;
                max_len = max(max_len, dp[r][c]);
            }
        }
        return max_len * max_len;
    }
};
