#include <vector>

using namespace std;


/**
 * 我设计了一套很复杂的规则来设置dp数组
 * 
 * 目的是处理负数配对的情况：
 * 当碰到一个负数，并且此前还有一个负数时，他们完成配对。
 * 此时dp[i]应该就是该负数和上一个0之间的所有数的乘积
 * 
 * 当nums[i]是负数时
 * 若没有与其配对的负数，那dp[i]就设置为该负数前的连续正数的乘积
 * 若该数前面是0，那dp[i]就设置为1
 * 
 * 当nums[i]是0，那dp[i]就设置为0
 * 
 * 当nums[i]是正数，那根据num[i-1]的正负情况以及负数的配对情况来设置dp[i]
 * 
 * 
 * 
 * 总结：太麻烦了，不能这么干，有更简洁的方法
 */
class Solution {
public:
  int maxProduct(vector<int>& nums) {
    int size = nums.size(); 
    int lastNegative = -1, lastZero = -1;
    vector<int> dp(size);
    dp[0] = nums[0];
    if(nums[0] < 0) {
      lastNegative = 0;
      dp[0] = 1;
    }
    int res = 0;
    
    for(int i = 1; i < size; i++) {
      if(nums[i] > 0) {
        if(dp[i - 1] == 0) dp[i] = nums[i];
        else {
          if(nums[i - 1] < 0) {
            if(lastNegative == -1) { //负数是两两配对的
              dp[i] = nums[i] * dp[i - 1];
            } else if(lastNegative == i - 1) { //存在没有配对的负数
              dp[i] = nums[i];
            }
          } else if(nums[i - 1] > 0) {
            dp[i] = nums[i] * dp[i - 1];
          }
        }
      } else if(nums[i] < 0) { //该数是负数
        if(lastNegative != -1) { //有一个和该负数配对的负数
          dp[i] = nums[i] * nums[lastNegative] * dp[lastNegative];
          if(lastNegative != i - 1) dp[i] *= dp[i - 1]; //两个负数连不连续
          lastNegative = -1; //配对完成
        } else { // 没有和该负数配对的负数
          lastNegative = i;
          if(dp[i - 1] == 0) dp[i] = 1;
          else dp[i] = dp[i - 1];
        }
      } else {
        dp[i] = 0;
      }
      

    }
    for(int i : dp) {
      res = max(i, res);
    }
    return res;
  }
};

/**
 * 
 */
class Solution {
public:
  int maxProduct(vector<int>& nums) {
    int size = nums.size();
    //dpMax[i]代表以nums[i]为结尾的子数组最大乘积的值
    //dpMin[i]代表以nums[i]为结尾的子数组最小乘积的值
    vector<int> dpMax(size), dpMin(size);
    dpMax[0] = dpMin[0] = nums[0];
    for(int i = 1; i < size; i++) {
      if(nums[i] == 0) dpMax[i] = dpMin[i] = 0;
      else if(nums[i] > 0) {
        if(dpMax[i - 1] > 0) {
          dpMax[i] = dpMax[i - 1] * nums[i];
        } else if(dpMax[i - 1] <= 0) {
          dpMax[i] = nums[i];
        }
        if(dpMin[i - 1] < 0) {
          dpMin[i] = nums[i] * dpMin[i - 1];
        } else if(dpMin[i - 1] >= 0) {
          dpMin[i] = nums[i];
        }
        //以上的if else判断可以简化为以下两句
        // dpMax[i] = max(dpMax[i - 1] * nums[i], nums[i]);
        // dpMin[i] = min(dpMin[i - 1] * nums[i], nums[i]);
      } else if(nums[i] < 0){
        if(dpMax[i - 1] > 0) {
          dpMin[i] = dpMax[i - 1] * nums[i];
        } else if(dpMax[i - 1] <= 0) {
          dpMin[i] = nums[i];
        }
        if(dpMin[i - 1] <= 0) {
          dpMax[i] = dpMin[i - 1] * nums[i];
        } else if(dpMin[i - 1] > 0) {
          dpMax[i] = nums[i];
        }
        //以上的if else判断可以简化为以下两句
        // dpMax[i] = max(dpMin[i - 1] * nums[i], nums[i]);
        // dpMin[i] = min(dpMax[i - 1] * nums[i], nums[i]);
      }
    }
    return ranges::max(dpMax);
  }
};

