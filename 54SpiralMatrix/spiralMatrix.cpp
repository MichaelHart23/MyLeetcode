#include <vector>

using namespace std;

class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<int> res;
    res.reserve(m * n);
    int left = 0, right = n - 1, up = 0, down = m - 1;
    auto check = [&]() {
      return left <= right && up <= down;
    };
    while(true) {
      for(int i = left; i <= right; i++)
        res.push_back(matrix[up][i]);
      up++;
      if(!check()) break;
      //可以直接优化成以下代码
      //if(++up > down) break;

      for(int j = up; j <= down; j++)
        res.push_back(matrix[j][right]);
      right--;
      if(!check()) break;

      for(int i = right; i>= left; i--) 
        res.push_back(matrix[down][i]);
      down--;
      if(!check()) break;

      for(int j = down; j >= up; j--)
        res.push_back(matrix[j][left]);
      left++;
      if(!check()) break;
    }
    return res;
  }
};

int main() {
  vector<vector<int>> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Solution s;
  s.spiralOrder(m);
}