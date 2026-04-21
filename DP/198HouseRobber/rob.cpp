#include <vector>

using namespace std;

class Solution {
public:
  int rob(vector<int>& nums) {
    int size = nums.size();
    vector<int> dp(size + 1, 0);
    dp[1] = nums[0];
    for(int i = 2; i < size + 1; i++) {
      dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1]);
    }
    return dp[size];
  }
};
