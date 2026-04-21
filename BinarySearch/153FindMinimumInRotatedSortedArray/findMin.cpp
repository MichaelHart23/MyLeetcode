#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int findMin(vector<int>& nums) {
    int left = 0, right = nums.size();
    int last = nums.back();
    while(left < right) {
      int mid = left + (right - left) / 2;
      if(nums[mid] <= last) {
        right = mid;
      } else if(nums[mid] > last) {
        left = mid + 1;
      }
    }
    return nums[left];
  }
};
