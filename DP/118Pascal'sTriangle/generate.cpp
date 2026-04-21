#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res(numRows);
    for(int i = 0; i < numRows; i++) {
      if(i == 0) res[i] = move(vector<int>(1, 1));
      else if(i == 1) res[i] = move(vector<int>(2, 1));
      else {
        res[i].push_back(1);
        for(int j = 1; j < i; j++) {
          res[i].push_back(res[i - 1][j - 1] + res[i - 1][j]);
        }
        res[i].push_back(1);
      }
    }
    return res;
  }
};
