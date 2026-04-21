#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
  void backtracking(vector<vector<int>>& res, vector<int>&vec, vector<bool>&selected, vector<int>& nums) {
    if(vec.size() == nums.size()) {
      res.push_back(vec);
      return;
    }
    int size = nums.size();
    for(int i = 0; i < size; i++) {
      if(selected[i]) continue;
      vec.push_back(nums[i]);
      selected[i] = true;
      backtracking(res, vec, selected, nums);
      selected[i] = false;
      vec.pop_back();
    }
  }
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    int nSelect = 0;
    vector<bool> selected(nums.size(), false); //记录哪些元素是被选过的
    vector<int> vec; //记录具体的排列
    backtracking(res, vec, selected, nums);
    return res;
  }
};

/**
 * 闭包简化版
 * 
 * 可以优化的地方：
 * 1 固定vec的大小，用一个nSelect遍历记录到第几个元素了，这样会少动态数组变大变小的开销
 * 
 */
class Solution {
    vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> res;
    int nSelect = 0, size = nums.size();
    vector<bool> selected(nums.size(), false); //记录哪些元素是被选过的
    vector<int> vec; //记录具体的排列
    auto backtracking = [&](this auto&& backtracking) {
      if(vec.size() == nums.size()) {
        res.push_back(vec); //直接在
        return;
      }
      for(int i = 0; i < size; i++) {
        if(!selected[i]) {
          selected[i] = true;
          vec.push_back(nums[i]);
          backtracking();
          vec.pop_back();
          selected[i] = false;
        }
      }
    };
    backtracking();
    return res;
  }
};
