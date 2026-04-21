#include <bits/stdc++.h>

using namespace std;


/**
 * 1 两串中相匹配的字符一定是在某个点匹配上的，一定是在某个点出现的s[i] == t[j]的
 * 2 
 */
class Solution {
public:
    int longestCommonSubsequence(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for(int i = 1; i < m + 1; i++) {
            for(int j = 1; j < n + 1; j++) {
                if(s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};

/**
 * 空间优化, 单数组 + 单变量
 */
class Solution {
public:
    int longestCommonSubsequence(string s, string t) {
        if(t.size() > s.size()) return longestCommonSubsequence(t, s); //选择较短的串作为列
        int m = s.size(), n = t.size();
        vector<int> dp(n + 1, 0);
        for(int i = 1; i < m + 1; i++) {
            int pre = 0;
            for(int j = 1; j < n + 1; j++) {
                int temp = dp[j];
                if(s[i - 1] == t[j - 1]) {
                    dp[j] = pre + 1;
                } else {
                    dp[j] = max(dp[j], dp[j - 1]);
                }
                pre = temp;
            }
        }
        return dp[n];
    }
};
int main() {
    string s1 = "abc", s2 = "def";
    Solution s;
    s.longestCommonSubsequence(s1, s2);
}
