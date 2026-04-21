#include <vector>

using namespace std;

/* 生成前缀和数组ps，问题就变成了找到i和j(0 <= i < j <= n)，使得ps[j] - ps[i]最大
 * 对前缀和再生成如下额外数组：
 * left_min: left_min[i]表示 "ps[i]以及ps[i]左边的数中最小的数"
 * right_max: right_max[i]表示 "ps[i]右边的数中最小的数". 注意：不包括ps[i]
 * 为什么left_min and right_max会有这个区别？
 * 有哪些边界情况呢？
 * 1 当数组仅有一个数
 * 2 当数组仅有一个数, 且该数是负数
 * 3 当答案是一个数, 也即没有任何子数组的和比该单单一个数更大
 * 当left_min 和 right_max 相同时
 * 即，当前缀和单调递减时
 */
class Solution {
public:
  int maxSubArray(vector<int>& nums) {
    int n = nums.size(), res = INT32_MIN;
    if(n == 1)
      return nums[0];
    vector<int> ps(n + 1), left_min(n + 1), right_max(n + 1);
    for(int i = 0; i < n; i++) { //合并生成前缀和数组和left_min数组
      ps[i + 1] = ps[i] + nums[i];
      left_min[i + 1] = min(left_min[i], ps[i]);
    }
    right_max[n] = ps[n];
    for(int i = n; i > 0; i--) {
      right_max[i - 1] = max(ps[i - 1], right_max[i]);
    }
    for(int i = 0; i < n + 1; i++) {
      int diff = right_max[i] - left_min[i];
      if(diff > res)
        res = diff;
    }
    return res;
  }
};

/* 以上方法行不通，当前缀和单调递减时，结果不正确
 * 还是前缀和，从左到右遍历前缀和，维护遍历到目前为止的最小前缀和
 * 用当前"前缀和"减去最小前缀和就是以当前元素为结尾的最大子数组和
 */
class Solution2 {
public:
  int maxSubArray(vector<int>& nums) {
    int res = INT32_MIN;
    int min_presum = 0; //前0项和是0, 所以一开始的最小前缀和初始化为0
    int presum = 0; //前0项和是0, 所以一开始的前缀和初始化为0
    for(int x : nums) {
      presum += x;
      res = max(res, presum - min_presum);
      min_presum = min(min_presum, presum);
    }
    return res;
  }
};


class SolutionDP{
  public:
  int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);
    int res = nums[0];
    dp[0] = nums[0];
    for(int i = 1; i < n; i++) {
      if(dp[i - 1] < 0) {
        dp[i] = nums[i];
      } else {
        dp[i] = nums[i] + dp[i - 1];
      }
      res = max(res, dp[i]);
    }
    return res;
  }
};
