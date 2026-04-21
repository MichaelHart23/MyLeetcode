#include <bits/stdc++.h>

using namespace std;

/**
 * 题目理解：
 * 1 s1.size + s2.size = s3.size
 * 2 s1 和 s2 的子串必须交替出现
 * 
 * 一从后往前想思路瞬间打开
 * 看s3能否被s1和s2表示就看s3的最后一个字符是否和s1或s2的最后一个字符相同
 * 如果和其中的某一个字符相同，那么就看 s3 - 1 能否被 s1 - 1 和 s2表示
 * 如果都相同，就看 s3 - 1 能否被 s1 - 1 s2 表示  或   s3 - 1 能否被 s1 和 s2 - 1 表示
 * 
 */
class Solution1 {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.size(), len2 = s2.size();
        if(s3.size() != len1 + len2) return false;
        //dp[i][j]表示s1的前i个字符和s2的前j个字符能否表示s3的前i+j个字符
        vector<vector<bool>> dp(len1 + 1, vector<bool>(len2 + 1, false));
        dp[0][0] = true;
        for(int i = 1; i < len1 + 1; i++) {
            dp[i][0] = dp[i - 1][0] && s3[i - 1] == s1[i - 1];
            if(!dp[i][0]) break;
        }
        for(int i = 1; i < len2 + 1; i++) {
            dp[0][i] = dp[0][i - 1] && s3[i - 1] == s2[i - 1];
            if(!dp[0][i]) break;
        }
        for(int i = 1; i < len1 + 1; i++) {
            for(int j = 1; j < len2 + 1; j++) {
                char c = s3[i + j - 1];
                if(c != s1[i - 1] && c != s2[j - 1]) {
                    dp[i][j] = false;
                } else if(c == s1[i - 1] && c != s2[j - 1]){
                    dp[i][j] = dp[i - 1][j];
                } else if(c != s1[i - 1] && c == s2[j - 1]) {
                    dp[i][j] = dp[i][j - 1];
                } else {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
            }
        }
        return dp[len1][len2];
    }
};

/**
 * 空间优化
 */
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() < s2.size()) return isInterleave(s2, s1, s3); //选较短的作为s2
        int len1 = s1.size(), len2 = s2.size();
        if(s3.size() != len1 + len2) return false;
        vector<bool> dp(len2 + 1, false);
        dp[0] = true;
        for(int i = 1; i < len2 + 1; i++) {
            dp[i] = dp[i - 1] && s2[i - 1] == s3[i - 1];
        }
        for(int i = 1; i < len1 + 1; i++) {
            dp[0] = dp[0] && s1[i - 1] == s3[i - 1];
            for(int j = 1; j < len2 + 1; j++) {
                char c = s3[i + j - 1];
                if(c != s1[i - 1] && c != s2[j - 1]) {
                    dp[j] = false;
                } else if(c == s1[i - 1] && c != s2[j - 1]){
                    dp[j] = dp[j];
                } else if(c != s1[i - 1] && c == s2[j - 1]) {
                    dp[j] = dp[j - 1];
                } else {
                    dp[j] = dp[j] || dp[j - 1];
                }
            }
        }
        return dp[len2];
    }
};


int main() {
    string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
    Solution s;
    s.isInterleave(s1, s2, s3);
}
