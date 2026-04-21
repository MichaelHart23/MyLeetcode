#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    int size = candidates.size(), sum = 0;
    sort(candidates.begin(), candidates.end()); //排序
    vector<vector<int>> res;
    vector<int> state;
    /**
     * 小小一个start就完成了剪枝，在下一轮中，所有包含start之前的元素的组合方式都已经探索过了
     * start之前的元素选更多次数的可能都已经探索过了
     */
    auto dfs = [&](this auto&& dfs, int start)->void{
      if(sum == target) {
        res.push_back(state);
        return;
      }
      for(int i = start; i < size; i++) {
        if(sum + candidates[i] > target) break;
        sum += candidates[i];
        state.push_back(candidates[i]);
        dfs(i);
        state.pop_back();
        sum -= candidates[i];
      }
    };
    dfs(0);
    return res;
  }
};

/**
 * 选或不选
 */
class Solution {
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    int size = candidates.size(), sum = 0;
    vector<vector<int>> res;
    vector<int> state;

    auto dfs = [&](this auto&& dfs, int i) -> void {
      if(sum == target) {
        res.push_back(state);
        return;
      } else if(sum > target || i == size) return;

      state.push_back(candidates[i]);
      sum += candidates[i];
      dfs(i);
      sum -= candidates[i];
      state.pop_back();

      dfs(i + 1);
    };
    dfs(0);
    return res;
  }
};
