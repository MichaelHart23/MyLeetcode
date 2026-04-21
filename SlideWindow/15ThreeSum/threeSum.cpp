#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    size_t size = nums.size();
    for(int k = 0; k < size - 2; k++) {
      if(nums[k] > 0) {
        break;
      }
      if(k > 0 && nums[k] == nums[k - 1]) {
        continue;
      }
      int i = k + 1, j = size - 1;
      while(i < j) {
        int sum = nums[k] + nums[i] + nums[j];
        if(sum > 0) {
          while(i < j && nums[j] == nums[--j]);
        } else if (sum < 0) {
          while(i < j && nums[i] == nums[++i]);
        } else {
          res.push_back({nums[k], nums[i], nums[j]});
          while(i < j && nums[j] == nums[--j]);
          while(i < j && nums[i] == nums[++i]);
        }
      }
    }
    return res;
  }
};