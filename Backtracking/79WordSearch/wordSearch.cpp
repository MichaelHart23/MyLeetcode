#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>

using namespace std;

/**
 * 深搜
 */
class Solution {
  int DIRS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // 四方向
 public:
  bool exist(vector<vector<char>>& board, string word) {
    int rows = board.size(), cols = board[0].size(), n = word.size();
    vector<vector<bool>> explored(rows, vector<bool>(cols, false));

    // grid[row][col]是不是word[expected]，是就继续深搜下去，不是就返回
    // 若最终能匹配完，返回true，匹配不了返回false
    auto dfs = [&](this auto&& dfs, int row, int col, int expected) {
      if (expected == n) return true;
      if (row < 0 || row >= rows || col < 0 || col >= cols ||
          explored[row][col] || board[row][col] != word[expected])
        return false;
      explored[row][col] = true;
      bool res = false;
      for (auto [x, y] : DIRS) {
        res = res || dfs(row + x, col + y, expected + 1);
      }
      explored[row][col] = false;
      return res;
    };

    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (board[row][col] == word[0] && dfs(row, col, 0)) {
          return true;
        }
      }
    }
    return false;
  }
};

/**
 * 两个优化：
 * 1 word里的某个字母是不是比board里出现的多，多则false
 * 2 word里首字母是否在board里出现的次数比尾字母多，多则反转word
 */
class Solution {
  static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

 public:
  bool exist(vector<vector<char>>& board, string word) {
    unordered_map<char, int> cnt;
    for (auto& row : board) { //统计board中每个字符出现的次数
      for (char c : row) {
        cnt[c]++;
      }
    }

    // 优化一
    unordered_map<char, int> word_cnt;
    for (char c : word) { //统计word中每个字母出现的次数，若多于board则返回
      if (++word_cnt[c] > cnt[c]) {
        return false;
      }
    }

    // 优化二
    if (cnt[word.back()] < cnt[word[0]]) { //比较尾字母和首字母出现的次数
      reverse(word.begin(), word.end());
    }

    int rows = board.size(), cols = board[0].size(), n = word.size();
    vector<vector<bool>> explored(rows, vector<bool>(cols, false));

    // grid[row][col]是不是word[expected]，是就继续深搜下去，不是就返回
    // 若最终能匹配完，返回true，匹配不了返回false
    auto dfs = [&](this auto&& dfs, int row, int col, int expected) {
      if (expected == n) return true;
      if (row < 0 || row >= rows || col < 0 || col >= cols ||
          explored[row][col] || board[row][col] != word[expected])
        return false;
      explored[row][col] = true;
      bool res = false;
      for (auto [x, y] : DIRS) {
        res = res || dfs(row + x, col + y, expected + 1);
      }
      explored[row][col] = false;
      return res;
    };

    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (board[row][col] == word[0] && dfs(row, col, 0)) {
          return true;
        }
      }
    }
    return false;
  }
};
