#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;

    vector<bool> cols(n, false); //每一列是否有queen

    //由于二维数组的内存特性，把左上角的元素，也就是二维数组的第一个元素，看作零点
    //以行标和列标作为坐标唯一定位一个元素

    //每条从左上到右下的对角线上是否有queen，每条对角线上的元素的行标减列标相同
    //范围是[-(n - 1), n - 1], 所以计算的时候需要偏移一下，加上（n - 1）
    vector<bool> diag1(2 * n - 1, false); 
    //每条从左下到右上的对角线上是否有queen，每条对角线的元素的坐标之和相同
    //范围是[0, 2n - 1]
    vector<bool> diag2(2 * n - 1, false);

    vector<string> grid(n, string(n, '.'));

    //行标为k的行怎么选
    auto backtrack = [&](this auto&& backtrack, int k) {
      if(k == n) {
        res.push_back(grid);
        return;
      }
      for(int i = 0; i < n; i++) {
        if(cols[i] || diag1[k - i + n - 1] || diag2[i + k]) continue;
        grid[k][i] = 'Q';
        cols[i] = diag1[k - i + n - 1] = diag2[i + k] = true;
        backtrack(k + 1);
        cols[i] = diag1[k - i + n - 1] = diag2[i + k] = false;
        grid[k][i] = '.';
      }
    };
    backtrack(0);
    return res;
  }
};
