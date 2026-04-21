#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (nums[mid] > target) {
        if (nums[mid] > nums[right]) {  // 左边大的占了大部分
          if (target >= nums[left]) {
            right = mid - 1;
          } else {
            left = mid + 1;
          }
        } else if (nums[mid] < nums[left]) {  // 右边小的占了大部分
          right = mid - 1;
        } else {  // 无交错
          right = mid - 1;
        }
      } else if (nums[mid] < target) {
        if (nums[mid] > nums[right]) {  // 左边大的占了大部分
          left = mid + 1;
        } else if (nums[mid] < nums[left]) {  // 右边小的占了大部分
          if (target > nums[right]) {
            right = mid - 1;
          } else {
            left = mid + 1;
          }
        } else {  // 无交错
          left = mid + 1;
        }
      } else
        return mid;
    }
    return -1;
  }
};

/**
 * 上面的做法是一次二分，分类讨论，不过我的分类讨论写的繁琐了
 * 更简洁的分类讨论基于：
 * 若一个元素大于数组最后一个元素，那么该元素在左边那一段里；反之，则在右边那一段里
 *
 * 而二分的本质就是要判断target是在mid的左边还是右边
 * 基于以上，先看target和mid是否分属不同段，若知道了他们所分属不同的段，就知道target在mid的左边还是右边了
 * 若是他们属于同一段，按正常二分的方法做就好了
 */
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int last = nums.back();
    int left = 0, right = nums.size() - 1;  // 闭区间
    while (left <= right) {                 // 闭区间不为空
      int mid = left + (right - left) / 2;
      if (target > last && nums[mid] <= last) {  // target 在第一段，x 在第二段
        right = mid - 1;                             // 下轮循环去左边找
      } else if (nums[mid] > last &&target <= last) { // x 在第一段，target 在第二段
        left = mid + 1;                           // 下轮循环去右边找
      } else if (nums[mid] > target) {  // 否则，x 和 target 在同一段
        right = mid - 1;
      } else if (nums[mid] < target) {
        left = mid + 1;
      } else
        return mid;
    }
    return -1;
  }
};

/**
 * 可以用两次二分的做法，第一次二分找到数组最小值，也就是两段的分界点
 * 之后看在target哪一段里就查哪一段
 */
class Solution {
  // 153. 寻找旋转排序数组中的最小值（返回的是下标）
  int findMin(vector<int>& nums) {
    int left = 0, right = nums.size();  
    while (left < right) {            
      int mid = left + (right - left) / 2;
      if (nums[mid] < nums.back()) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return right;
  }

  // 有序数组中找 target 的下标
  int lower_bound(vector<int>& nums, int left, int right, int target) {
    while (left + 1 < right) {  // 开区间不为空
      // 循环不变量：
      // nums[right] >= target
      // nums[left] < target
      int mid = left + (right - left) / 2;
      if (nums[mid] >= target) {
        right = mid;  // 范围缩小到 (left, mid)
      } else {
        left = mid;  // 范围缩小到 (mid, right)
      }
    }
    return nums[right] == target ? right : -1;
  }

 public:
  int search(vector<int>& nums, int target) {
    int i = findMin(nums);
    if (target > nums.back()) {                 // target 只可能在第一段
      return lower_bound(nums, -1, i, target);  // 开区间 (-1, i)
    }
    // target 只可能在第二段
    // 由于此时 target <= nums[n-1]，所以 lower_bound 中的循环结束后，right < n
    // 一定成立，无需判断 right == n
    return lower_bound(nums, i - 1, nums.size(), target);  // 开区间 (i-1, n)
  }
};

int main() {
  vector<int> v = {4, 5, 6, 7, 8, 1, 2, 3};
  Solution s;
  s.search(v, 8);
}
