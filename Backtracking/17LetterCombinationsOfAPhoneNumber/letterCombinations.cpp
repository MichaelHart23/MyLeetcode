#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>


using namespace std;



class Solution {
public:
  vector<string> digitsMap;
  Solution() {
    digitsMap = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  }
  string& getLetters(char c) {
    return digitsMap[c - '2'];
  }
  vector<string> letterCombinations(string digits) {
    int n = digits.size();
    vector<string> res;
    string str;

    auto dfs = [&](this auto&& dfs, int i){
      if(i == n) {
        res.push_back(str);
        return;
      }
      string& s = getLetters(digits[i]);
      for(char c : s) {
       str.push_back(c);
        dfs(i + 1);
        str.pop_back();
      }
    };
    dfs(0);
    return res;
  }
};


/**
 * 优化了字符串变长变短的开销
 * 以及一次函数调用的开销
 */
class Solution {
public:
  vector<string> digitsMap;
  Solution() {
    digitsMap = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  }
  vector<string> letterCombinations(string digits) {
    int n = digits.size();
    vector<string> res;
    string str(n, 0);
    auto dfs = [&](this auto&& dfs, int i){
      if(i == n) {
        res.push_back(str);
        return;
      }
      string& s = digitsMap[digits[i] - '2'];
      for(char c : s) {
        str[i] = c;
        dfs(i + 1);
      }
    };
    dfs(0);
    return res;
  }
};
