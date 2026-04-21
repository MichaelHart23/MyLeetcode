#include <vector>

using namespace std;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size(), cols = matrix[0].size();
    int up = 0, down = rows;  // 上闭下开区间
    // 要找到第一个不大于target的数，区间的更新上要注意
    while (up < down) {
      int mid = up + (down - up) / 2;
      if (matrix[mid][0] > target) {
        down = mid;  // down是开区间，舍弃mid
      } else if (matrix[mid][0] < target) {
        up = mid + 1;  // 该mid也许就是最后一个小于target的，所以不舍弃
      } else
        return true;
    }
    int row = up - 1;
    if (row < 0) return false;
    int left = 1,
        right = cols;  // 左闭右开区间, 且已经确定第一个元素不是目标了
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (matrix[row][mid] > target) {
        right = mid;  // right是开区间，舍弃mid
      } else if (matrix[row][mid] < target) {
        left = mid + 1;
      } else
        return true;
    }
    return false;
  }
};

/**
 * 把整个矩阵当成一个一维数组来二分，不用两次二分了
 */
class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n;
    while (left < right) {
      int mid = left + (right - left) / 2;
      int x = matrix[mid / n][mid % n];
      if (x > target) {
        right = mid;
      } else if (x < target) {
        left = mid + 1;
      } else
        return true;
    }
    return false;
  }
};

/**
 * 矩阵搜索法，适用与每行每列都是递增的矩阵
 * 从右上角开始，如果当前元素比target大，那么这一列剩余元素都比target大，排除这一列；
 * 如果当前元素比target小，那么这一行剩余元素都比target小，排除这一行
 */
class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int i = 0, j = n - 1;
    while (i < m && j >= 0) {  // 还有剩余元素
      if (matrix[i][j] == target) {
        return true;  // 找到 target
      }
      if (matrix[i][j] < target) {
        i++;  // 这一行剩余元素全部小于 target，排除
      } else {
        j--;  // 这一列剩余元素全部大于 target，排除
      }
    }
    return false;
  }
};
