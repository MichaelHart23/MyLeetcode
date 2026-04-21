#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols));
        dp[0][0] = grid[0][0];
        for(int col = 1; col < cols; col++) dp[0][col] = dp[0][col - 1] + grid[0][col];
        for(int row = 1; row < rows; row++) dp[row][0] = dp[row - 1][0] + grid[row][0];

        for(int i = 1; i < rows; i++) {
            for(int j = 1; j < cols; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[rows - 1][cols - 1];
    }
};
