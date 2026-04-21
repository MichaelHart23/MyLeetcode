#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int rows = obstacleGrid.size(), cols = obstacleGrid[0].size();
        if(obstacleGrid[rows - 1][cols - 1] == 1 || obstacleGrid[0][0] == 1) return 0;
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        for(int row = 0; row < rows; row++) {
            if(obstacleGrid[row][0] == 1) break;
            else dp[row][0] = 1;
        }
        for(int col = 0; col < cols; col++) {
            if(obstacleGrid[0][col] == 1) break;
            else dp[0][col] = 1; 
        }
        for(int row = 1; row < rows; row++) {
            for(int col = 1; col < cols; col++) {
                dp[row][col] = obstacleGrid[row][col] == 1 ? 0 
                            : dp[row][col - 1] + dp[row - 1][col];
            }
        }
        return dp[rows - 1][cols - 1];
    }
};

int main() {
    vector<vector<int>> vv;
    vv.push_back({0, 1, 0, 0});
    Solution s;
    s.uniquePathsWithObstacles(vv);
}
