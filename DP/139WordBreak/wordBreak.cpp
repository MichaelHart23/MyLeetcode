#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool wordBreak(string s, vector<string>& wordDict) {
    int strLen = s.size();
    int dictSize = wordDict.size();
    //dpFront[i][n]表示前i个单词能否组成由s的前n个字符形成的子串
    vector<vector<bool>> dpFront(dictSize + 1, vector<bool>(strLen + 1, false));
    //dpBack[i][n]表示前i个单词能否组成由s的倒数n个字符形成的子串
    vector<vector<bool>> dpBack(dictSize + 1, vector<bool>(strLen + 1, false));
    dpFront[0][0] = dpBack[0][0] = true;

    for(int i = 1; i < dictSize + 1; i++) {
      for(int n = 0; n < strLen + 1; n++) {
        if(n == 0) {
          dpFront[i][0] = dpBack[i][0] = true;
          continue;
        }
        if(wordDict[i - 1].size() > n) {
          dpFront[i][n] = dpFront[i - 1][n];
          dpBack[i][n] = dpBack[i - 1][n];
          continue;
        }
        int index;
        if((index = s.substr(0, n).find(wordDict[i - 1])) != string::npos) {
          dpFront[i][n] = dpFront[i][index] && dpBack[i][n - index - wordDict[i - 1].size()];
        } else {
          dpFront[i][n] = dpFront[i - 1][n];
        }
        if((index = s.substr(strLen - n, n).find(wordDict[i - 1])) != string::npos) {
          
        } else {}
      }
    }


  }
};

/**
 * 和coinChange问题有些类似，只不过coinChange是单纯的数值累加，而这个涉及到单词的组合顺序为题
 * 
 * 我想叫他步长探测法，dp[i]表示s中前i个字符组成的子串能否被表示，那么对于每个i，如果dp[i]为true，那么就以i为起点，
 * 探测wordDict中的单词，如果有单词和s中以i为起点的子串相等，那么就把dp[i + word.size()]置为true
 */
class Solution {
public:
  bool wordBreak(string s, vector<string>& wordDict) {
    int strLen = s.size();
    vector<bool> dp(strLen + 1, false); //dp[i]表示s中前i个字符组成的子串能否被表示
    dp[0] = true;
    for(int i = 0; i < strLen + 1; i++) {
      if(!dp[i]) continue;
      for(auto& word : wordDict) {
        if(i + word.size() <= strLen && word == s.substr(i, word.size())) 
          dp[i + word.size()] = true;
      }
    }
    return dp[strLen];
  }
};

