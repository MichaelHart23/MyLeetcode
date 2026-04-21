#include <deque>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * 广搜
 */
class Solution {
  struct Pos {
    int row;
    int col;
    Pos() : row(0), col(0) {}
    Pos(int r, int c) : row(r), col(c) {}
  };
  int x[4];
  int y[4];

 public:
  Solution() {
    x[0] = 1, y[0] = 0;
    x[1] = 0, y[1] = 1;
    x[2] = -1, y[2] = 0;
    x[3] = 0, y[3] = -1;
  }
  int orangesRotting(vector<vector<int>>& grid) {
    int res = 0, freshOranges = 0;
    deque<Pos> que;
    int rows = grid.size(), cols = grid[0].size();
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < cols; col++) {
        if (grid[row][col] == 1)
          freshOranges++;
        else if (grid[row][col] == 2)
          que.emplace_back(row, col);
      }
    }
    if (freshOranges == 0) return 0;
    auto isFresh = [&](int row, int col) -> bool {
      if (row >= 0 && row < rows && col >= 0 && col < cols &&
          grid[row][col] == 1) {
        return true;
      }
      return false;
    };
    while (!que.empty()) {
      deque<Pos> newRot;
      for (Pos p : que) {
        for (int i = 0; i < 4; i++) {
          int row = p.row + x[i], col = p.col + y[i];
          if (isFresh(row, col)) {
            grid[row][col] = 2;
            newRot.emplace_back(row, col);
            freshOranges--;
          }
        }
      }
      if (!newRot.empty()) res++;
      que = move(newRot);
    }
    return freshOranges != 0 ? -1 : res;
  }
};

/**
 * 另一种更简洁的对于方向和位置的表示
 * 用一行二维数组表示方向，用对组表示位置，同时利用auto[x, y]获取对组的元素
 */
class Solution {
  int DIRECTIONS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // 四方向
 public:
  int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    int fresh = 0;
    vector<pair<int, int>> q;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          fresh++;  // 统计新鲜橘子个数
        } else if (grid[i][j] == 2) {
          q.emplace_back(i, j);  // 一开始就腐烂的橘子
        }
      }
    }

    int ans = 0;
    while (fresh && !q.empty()) {
      ans++;  // 经过一分钟
      vector<pair<int, int>> nxt;
      for (auto& [x, y] : q) {       // 已经腐烂的橘子
        for (auto d : DIRECTIONS) {  // 四方向
          int i = x + d[0], j = y + d[1];
          if (0 <= i && i < m && 0 <= j && j < n &&
              grid[i][j] == 1) {  // 新鲜橘子
            fresh--;
            grid[i][j] = 2;  // 变成腐烂橘子
            nxt.emplace_back(i, j);
          }
        }
      }
      q = move(nxt);
    }

    return fresh ? -1 : ans;
  }
};
