#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        // 简单的组合方式，也可以使用 boost::hash_combine
        return h1 ^ (h2 << 1);
    }
};

class Solution {
public:
  struct Island {
    unordered_set<pair<int, int>, pair_hash> lands;
    void add(int row, int col) { lands.insert(make_pair(row, col));}
    void add(pair<int, int> p) { lands.insert(p);}
    bool contains(int row, int col) { return lands.contains(make_pair(row, col)); }
    bool contains(pair<int, int> p) { return lands.contains(p); }
  };
  vector<Island> islands;
  int rows;
  int cols;
  int x[4];
  int y[4];

  Solution() {
    x[0] = 1, y[0] = 0;
    x[1] = 0, y[1] = 1;
    x[2] = -1, y[2] = 0;
    x[3] = 0, y[3] = -1;
  }

  void isLand(vector<vector<char>>& grid,  deque<pair<int, int>>& que, Island& island, int row, int col) {
    pair<int, int> p = make_pair(row, col);
    //没越界，是land，而且还没被包含在island中
    if(row >= 0 && col >= 0 && row < rows && col < cols && grid[row][col] == '1' && !island.contains(p)) {
      que.push_back(p);
      island.add(p);
    }
  }

  void bfs(vector<vector<char>>& grid, int row, int col) {
    deque<pair<int, int>> que;
    Island island;
    que.push_back(make_pair(row, col));
    while(!que.empty()) {
      auto [row, col] = que.front();
      que.pop_front();
      for(int i = 0; i < 4; i++)
        isLand(grid, que, island,row + x[i], col + y[i]);
    }
    islands.push_back(island);
  }

  //该陆地是否被探索过了
  bool isExplored(int row, int col) {
    for(auto& island : islands) {
      if(island.contains(make_pair(row, col))) 
        return true;
    }
    return false;
  }
  
  int numIslands(vector<vector<char>>& grid) {
    rows = grid.size(), cols = grid[0].size();
    int res = 0;
    for(int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
        if(grid[i][j] == '1' && !isExplored(i, j)) {
          bfs(grid, i, j);
          res++;
        }
      }
    }
    return res;
  }
};


/**
 * 优化：
 * 不需要用set来记录哪些land被访问过，直接在原数组上标记就行
 * 也不需要不同岛屿不同记录，一个岛屿经过bfs到不了其他岛屿
 */

class Solution {
  int x[4];
  int y[4];
public:
  Solution() {
    x[0] = 1, y[0] = 0;
    x[1] = 0, y[1] = 1;
    x[2] = -1, y[2] = 0;
    x[3] = 0, y[3] = -1;
  }
  int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), res = 0;

    auto dfs = [&](this auto&& dfs, int row, int col) {
      if(row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col] != '1') {
        return;
      }
      grid[row][col] = '2';
      for(int i = 0; i < 4; i++) {
        dfs(row + x[i], col + y[i]);
      }
    };

    for(int row = 0; row < rows; row++) {
      for(int col = 0; col < cols; col++) {
        if(grid[row][col] == '1') {
          dfs(row, col);
          res++;
        }
      }
    }

    return res;
  }
};
