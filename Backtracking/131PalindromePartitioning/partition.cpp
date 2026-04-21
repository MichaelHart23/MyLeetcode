#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>

using namespace std;


/**
 * 下面两种解法的问题是，对每一种划分方式都要判断回文串的开销，能不能省去这个开销呢？
 * 留作之后思考吧
 */
class Solution {
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> strs;
    int size = s.size();

    auto backtrack = [&] (int x) {
      if(x == size) return;
      int left = x, right = x;
      while(left >= 0 && right < size && s[left] == s[right]) {
        
        left--;
        right++;
      }
      
    };
  }
};


/**
 * 枚举怎么把原字符串切分成子串的切分情况
 * 然后筛选其中切成回文串的情况加入答案
 * 
 * 简言之：
 * 枚举所有切分方案，把切成回文串的情况加入答案
 * 
 * 怎么枚举？
 * 每一个字符的后面，要不要插入分隔符，也就是要不要切分
 * 总共2^n种情况
 */
class Solution {
  bool isPalindrome(const string& str, int start, int end) {
    while(start < end) {
      if(str[start++] != str[end--])
       return false;
    }
    return true;
  }
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> state;
    int n = s.size();
    //s[x]到s[n-1]这些元素后的分隔符怎么放，s[x]前面已经有一个分隔符了
    //已经被分隔符隔出来的部分都确定是回文串
    auto dfs = [&](this auto&& dfs, int x) {
      if(x == n) { //为什么需要x==size才return，因为确实要判断一遍s[n-1]后要不要放分隔符
        res.push_back(state);
        return;
      }
      //枚举下一个分隔符放哪才能隔出一个回文串来，隔不出来的相当于被剪枝了
      for(int i = x; i < n; i++) {
        //在s[i]后面放了分隔符，隔出来的部分是[x, i]
        if(isPalindrome(s, x, i)) {
          state.push_back(s.substr(x, i - x + 1));
          dfs(i + 1);
          state.pop_back();
        }
      }
    };
    dfs(0);
    return res;
  }
};

/**
 * 这个解法和上面那个解法思路是一样的，这个解法是在每个递归单元里枚举一个位置发分隔符要不要放
 */
class Solution {
  bool isPalindrome(const string& str, int start, int end) {
    while(start < end) {
      if(str[start++] != str[end--])
       return false;
    }
    return true;
  }
public:
  vector<vector<string>> partition(string s) {
    vector<vector<string>> res;
    vector<string> state;
    int n = s.size();
    //仅s[x]后面一个位置的的分隔符怎么放，s[x]前面已经有一个分隔符了
    //已经确定的分隔符隔出来的部分都确定是回文串
    //last代表上一个分隔符在哪里，具体是上一个分隔符后面是哪个元素
    auto dfs = [&](this auto&& dfs, int last, int x) {
      if(x == n) {
        return;
      }
      //放分隔符，并且可以分隔成回文串
      if(isPalindrome(s, last, x)) {
        state.push_back(s.substr(last, x - last + 1));
        if(x == n - 1) res.push_back(state);
        else dfs(x + 1, x + 1);
        state.pop_back();
      }
      //不放分隔符
      dfs(last, x + 1);
    };
    dfs(0, 0);
    return res;
  }
};
