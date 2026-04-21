#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    int minDistance(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for(int i = 1; i < n + 1; i++) {
            dp[0][i] = i;
        }
        for(int i = 1; i < m + 1; i++) {
            for(int j = 0; j < n + 1; j++) {
                if(j == 0) {
                    dp[i][0] = i;
                    continue;
                }
                int temp = min(dp[i - 1][j], dp[i][j - 1]) + 1;
                dp[i][j] = min(dp[i - 1][j - 1] + (s[i - 1] != t[j - 1]), temp); 
            }
        }
        return dp[m][n];
    }
};
