#include <vector>
#include <string>

using namespace std;


class Solution {
public:
  bool isMatch(string s, string p) {
    int sSize = s.size(), pSize = p.size();
    vector<vector<bool>> dp(sSize + 1, vector<bool>(pSize + 1, false));
    // dp中相对于两字符串多了一行和一列
    dp[0][0] = 1;
    for(int row = 1; row < sSize + 1; row++) {
      dp[row][0] = false;
    }
    for(int col = 2; col < pSize + 1; col += 2) {
      dp[0][col] = dp[0][col - 2] && p[col - 1] == '*';
    }
    for(int row = 1; row < sSize + 1; row++) {
      for(int col = 1; col < pSize + 1; col++) {
        if(p[col - 1] == '*') {
          dp[row][col] = dp[row][col - 2] || (dp[row - 1][col] && s[row - 1] == p[col - 2]) || (dp[row - 1][col] && p[col - 2] == '.');
        }
        else {
          dp[row][col] = dp[row - 1][col - 1] && (p[col - 1] == '.' || p[col - 1] == s[row - 1]);
        }
      }
    }
    return dp[sSize][pSize];
  }
};

/**
 * dp动态规划:
 * 1 首行的初始化，注意当*出现在偶数位置上时，正则表达式可能可以匹配空串
 * 2 当遍历到*的位置上时的状态转移，不从多了一个*的表达式角度去考虑，反而从多路一个字符的原串角度去考虑
 */
class Solution {
public:
  bool isMatch(string s, string p) {
    int sSize = s.size(), pSize = p.size();
    vector<vector<bool>> dp(sSize + 1, vector<bool>(pSize + 1, false));
    // dp中相对于两字符串多了一行和一列
    dp[0][0] = 1;
    for(int row = 1; row < sSize + 1; row++) {
      dp[row][0] = false;
    }
    for(int col = 2; col < pSize + 1; col += 2) {
      dp[0][col] = dp[0][col - 2] && p[col - 1] == '*';
    }
    for(int row = 1; row < sSize + 1; row++) {
      for(int col = 1; col < pSize + 1; col++) {
        if(p[col - 1] == '*') {
          if(dp[row - 1][col] == false) {
            // 本来原串和表达式匹配不上，原串加了一个字符之后匹配上了，说明匹配上了 *起消除一个字符的作用的那个串
            if(dp[row][col - 2] == true) {
              dp[row][col] = true;
            }
          } else if(dp[row - 1][col] == true) {
            //本来原串能匹配的上，原串加了一个字符之后仍然能和表达式匹配上，说明加上的是表达式中*之前的那个字符，也可能那个字符是 .
            if(s[row - 1] == p[col - 2] || p[col - 2] == '.') {
              dp[row][col] = true;
            }
          }
        }
        else {
          dp[row][col] = dp[row - 1][col - 1] && (p[col - 1] == '.' || p[col - 1] == s[row - 1]);
        }
      }
    }
    return dp[sSize][pSize];
  }
};
