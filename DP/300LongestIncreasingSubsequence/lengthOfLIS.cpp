#include <vector>

using namespace std;


/**
 * 理解错题意了，我写的最长“连续”递增子序列，题目本身不要求连续
 */
class Solution {
public:
  int lengthOfLIS(vector<int>& nums) {
    int size = nums.size(), res = 0;
    vector<int> dp(size + 1, 0); //dp[i]表示以第i个元素为结尾的最长连续递增子序列的长度
    dp[1] = 1;
    for(int i = 2; i < size + 1; i++) {
      if(nums[i - 1] > nums[i - 2]) dp[i] = dp[i - 1] + 1;
      else dp[i] = 1;
      res = max(dp[i], res);
    }
    return res;
  }
};

class Solution {
public:
  int lengthOfLIS(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    int size = nums.size(), res = 1;
    vector<int> dp(size, 1);//dp[i]表示以原数组下标为i的元素结尾的LIS
    for(int i = 1; i < size; i++) {
      for(int j = 0; j < i; j++) {
        if(nums[j] < nums[i]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
        res = max(res, dp[i]);
      }
    }
    return res;
  }
};

/**
 * 一种贪心+二分的的非常巧妙的解法
 */


class Solution {
public:
  //查找升序数组g中第一个不小于target的元素的index，都小于target返回g的长度
  // 如果采用双闭区间的写法：
  /**
   * left和right对于mid的更新很有门道:
   * 如果g[mid] < target，那么mid肯定不是要找的下标，所以可以舍弃，left = mid + 1
   * 如果g[mid] >= target，那么mid可能是要找的下标，所以不能舍弃，right = mid
   * 双闭区间的话，如果target大于g中的所有元素，会不能正确返回g.size()
   * 要能返回需要写成 left <= right, 但这样又会在target小于g中所有元素的时候陷入死循环
   */
  //这是双闭区间的写法
  int search_(vector<int>& g, int target) {
    int left = 0, right = g.size() - 1;
    if(g.size() == 0) return 0;
    if(g[right] < target) return g.size(); //特殊情况单独处理
    if(g[left] > target) return 0;
    while(left < right) {
      int mid = (left + right) / 2;
      if(g[mid] < target) {
        left = mid + 1;
      } else if(g[mid] >= target) {
        right = mid;
      }
    }
    return left;
  }
  // 所以采用左闭右开区间的写法, 左闭右开也是更常用的写法
  // 当g[mid] >= target，mid = right看似在区间里舍弃了mid，其实没有舍弃
  // left和right依然有可能在这里碰头
  int search(vector<int>& g, int target) {
    int left = 0, right = g.size();
    while(left < right) {
      //int mid = (left + right) / 2;
      int mid = left + (right - left) / 2; //这样写能避免当left和right很大时，整数溢出的风险
      // 以上两种写法虽然数学上等价，但第二种写法能避免大数溢出
      if(g[mid] < target) {
        left = mid + 1;
      } else if(g[mid] >= target) {
        right = mid;
      }
    }
    return left; 
  }

  
  int lengthOfLIS(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    int size = nums.size();
    vector<int> g; //g[i]表示长为i+1的LIS的末尾值
    for(int i : nums) {
      int index = search(g, i);
      if(index == g.size()) {
        g.push_back(i);
      } else {
        g[index] = i;
      }
    }
    return g.size();
  }
};
