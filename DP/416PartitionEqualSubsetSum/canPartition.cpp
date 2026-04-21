#include <vector>
#include <ranges>

using namespace std;

/**
 * 找到一组序列，使其和为 sum / 2，本质为0-1背包问题
 */
class Solution {
public:
  bool canPartition(vector<int>& nums) {
    int totalSum = 0, size = nums.size();
    for(int i : nums) totalSum += i;
    if(totalSum % 2 != 0) return false; //若总和是奇数，不可能分割
    int target = totalSum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    for(int i = 1; i < size; i++) {
      for(int sum = target; sum > 0; sum--) {
        if(nums[i - 1] > sum) continue;
        dp[sum] = dp[sum] || dp[sum - nums[i - 1]];
      }
    }
    return dp[target];
  }
};
