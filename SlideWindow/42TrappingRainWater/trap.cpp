#include <vector>
#include <iostream>

using namespace std;

//从上到下一行一行算
class Solution1 {
public:
  int trap(vector<int>& height) {
    int size = height.size();
    int left = 0, right = size - 1;
    while(left < size && height[left] == 0) left++;
    while(right >= 0 && height[right] == 0) right--;
    int res = 0;
    for(int i = left; i < right; i++) { //以第i个位置为左边界
      for(int j = height[i]; j > 0; j--) { //从该位置最高处到最低处的遍历
        for(int k = i + 1; k <= right; k++) { //为该高度寻找右边界
          if(height[k] >= j) {
            res += (k - i - 1);
            break;
          }
        }
      }
    }
    return res;
  }
};

//单调栈的雏形，直接计算两个相对高的墙壁能围起多少水来
class Solution2 {
public:
  int calculate(vector<int>& height, int left, int right) {//计算left和right之间能围多少水
    int blocks = 0;
    for(int k = left + 1; k < right; k++) {
      blocks += height[k];
    }
    return (right - left - 1) * std::min(height[left], height[right]) - blocks;
  }
  int trap(vector<int>& height) {
    int size = height.size();
    int left = 0, right = size - 1;
    while(left < size && height[left] == 0) left++;
    while(right >= 0 && height[right] == 0) right--;
    int res = 0;
    for(int i = left; i < right; ) { //以i为最左边界
      int j = i + 1;
      int max_right = j;
      for(j = i + 1; j <= right; j++) {
        if(height[j] >= height[i]) { //能找到一个 >= 左边界高度的值
          res += calculate(height, i, j);
          i = j;
          max_right = -1;
          break;
        } else {
          if(height[j] >= height[max_right]) {
            max_right = j;
          }
        }
      }
      if(max_right != -1) { //没能找到一个 >= 左边界高度的值
        res += calculate(height, i, max_right);
        i = max_right;
      }
    }
    return res;
  }
};

int main() {
}