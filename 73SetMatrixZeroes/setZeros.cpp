#include <vector>

using namespace std;

/**
 * 思路演化与优化参见0x3f的题解
 * 该题目主要是空间的优化，而是时间
 * 
 * 
 */
class Solution {
public:
  void setZeroes(vector<vector<int>>& matrix) {
    bool first_row_has_zero = false;
    for(auto i : matrix[0]) {
      if(i == 0) {
        first_row_has_zero = true;
        break;
      }
    }
    int row_num = matrix.size(), col_num = matrix[0].size();
    //该循环合并了第一个的设置与“除第一列和第一行的设置”
    for(int i = 1; i < row_num; i++) {
      for(int j = 0; j < col_num; j++) {
        if(matrix[i][j] == 0) {
          matrix[i][0] = matrix[0][j] = 0;
        }
      }
    }
    for(int i = 1; i < row_num; i++) {
      for(int j = col_num - 1; j >= 0; j--) {
        if(matrix[i][0] == 0 || matrix[0][j] == 0) {
          matrix[i][j] = 0;
        }
      }
    }
    if(first_row_has_zero) {
      for(int i = 0; i < col_num; i++) {
        matrix[0][i] = 0;
      }
    }
  }
};

int main() {
  Solution s;
  vector<vector<int>> matrix = {{1,1,1},{1,0,1},{1,1,1}};
  s.setZeroes(matrix);
  return 0;
}