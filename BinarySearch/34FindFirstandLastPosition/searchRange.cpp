#include <iostream>
#include <vector>
using namespace std;

/**
 * 递归二分，不断向左区间递归搜索最左边的target，不断向右区间递归搜索最右边的target
 * 维护额外变量来记录结果
 */
class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res(2, -1);
    int size = nums.size();
    int leftPos = size, rightPos = -1;

    auto recurSearch = [&](this auto&& recurSearch, int left, int right,
                           bool searchLeft) -> void {
      if (right < left || nums[right] < target || nums[left] > target)
        return;  // 剪枝
      while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > target) {
          right = mid - 1;
        } else if (nums[mid] < target) {
          left = mid + 1;
        } else {
          if (searchLeft) {
            leftPos = min(leftPos, mid);
            recurSearch(left, mid - 1, searchLeft);
          } else {
            rightPos = max(rightPos, mid);
            recurSearch(mid + 1, right, searchLeft);
          }
          break;
        }
      }
    };

    // 对总区间进行一次二分，不然就要对整个区间进行两次二分了
    int left = 0, right = size - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] > target) {
        right = mid - 1;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else {
        leftPos = min(leftPos, mid);
        rightPos = max(rightPos, mid);
        recurSearch(left, mid - 1, true);
        recurSearch(mid + 1, right, false);
        break;
      }
    }
    if (leftPos == size) return res;
    res[0] = leftPos, res[1] = rightPos;
    return res;
  }
};

/**
 * 两次二分就够了
 * 如果递归方式是找最后一个不大于某个target的数，那第一次按target递归，第二次按target+1递归
 */
class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int size = nums.size();
    // 找到最大的小于target的数
    auto recurSearch = [&](this auto&& recurSearch, int left, int right,
                           int target) -> int {
      int ans = -1;  // 额外遍历和闭区间查找完成目标
      while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target) {
          right = mid - 1;
        } else if (nums[mid] < target) {
          ans = mid;
          left = mid + 1;
        }
      }
      return ans;
    };

    int leftPos = recurSearch(0, size - 1, target);
    if (leftPos >= size - 1 || nums[leftPos + 1] != target) return {-1, -1};
    int rightPos = recurSearch(0, size - 1, target + 1);
    return {leftPos + 1, rightPos};
  }
};

/**
 * 依旧是两次二分的写法，不过这次是思想是最小的满足 nums[i] >= target 的下标 i
 * 即找到最左边的，不小于target的元素
 * 对target和target + 1分别二分
 */
class Solution {
  // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
  // 如果数组为空，或者所有数都 < target，则返回 nums.size()
  // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
  int lower_bound(vector<int>& nums, int target) {
    int left = 0, right = (int)nums.size() - 1;  // 闭区间 [left, right]
    while (left <= right) {                      // 区间不为空
      // 循环不变量：
      // nums[left-1] < target
      // nums[right+1] >= target
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid - 1;  // 范围缩小到 [left, mid-1]
      } else {
        left = mid + 1;  // 范围缩小到 [mid+1, right]
      }
    }
    // 循环结束后 left = right+1
    // 此时 nums[left-1] < target 而 nums[left] = nums[right+1] >= target
    // 所以 left 就是第一个 >= target 的元素下标
    return left;
  }

 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = lower_bound(nums, target);
    if (start == nums.size() || nums[start] != target) {
      return {-1, -1};  // nums 中没有 target
    }
    // 如果 start 存在，那么 end 必定存在
    int end = lower_bound(nums, target + 1) - 1;
    return {start, end};
  }
};

class Solution {
  // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
  // 如果数组为空，或者所有数都 < target，则返回 nums.size()
  // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
  int lower_bound(vector<int>& nums, int target) {
    int left = 0, right = nums.size();  // 左闭右开区间 [left, right)
    while (left < right) {              // 区间不为空
      // 循环不变量：
      // nums[left-1] < target
      // nums[right] >= target
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid;  // 范围缩小到 [left, mid)
      } else {
        left = mid + 1;  // 范围缩小到 [mid+1, right)
      }
    }
    // 循环结束后 left = right
    // 此时 nums[left-1] < target 而 nums[left] = nums[right] >= target
    // 所以 left 就是第一个 >= target 的元素下标
    return left;
  }

 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = lower_bound(nums, target);
    if (start == nums.size() || nums[start] != target) {
      return {-1, -1};  // nums 中没有 target
    }
    // 如果 start 存在，那么 end 必定存在
    int end = lower_bound(nums, target + 1) - 1;
    return {start, end};
  }
};

class Solution {
  // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
  // 如果数组为空，或者所有数都 < target，则返回 nums.size()
  // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
  int lower_bound(vector<int>& nums, int target) {
    int left = -1, right = nums.size();  // 开区间 (left, right)
    while (left + 1 < right) {           // 区间不为空
      // 循环不变量：
      // nums[left] < target
      // nums[right] >= target
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid;  // 范围缩小到 (left, mid)
      } else {
        left = mid;  // 范围缩小到 (mid, right)
      }
    }
    // 循环结束后 left+1 = right
    // 此时 nums[left] < target 而 nums[right] >= target
    // 所以 right 就是第一个 >= target 的元素下标
    return right;
  }

 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = lower_bound(nums, target);
    if (start == nums.size() || nums[start] != target) {
      return {-1, -1};  // nums 中没有 target
    }
    // 如果 start 存在，那么 end 必定存在
    int end = lower_bound(nums, target + 1) - 1;
    return {start, end};
  }
};

int main() {
  vector<int> nums = {5, 7, 7, 8, 8, 10};
  int target = 8;
  Solution sol;
  vector<int> res = sol.searchRange(nums, target);
  cout << res[0] << " " << res[1] << endl;
}
