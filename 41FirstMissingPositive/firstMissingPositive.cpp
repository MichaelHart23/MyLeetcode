#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    auto swap = [&](int i, int j) {
      int temp = nums[j];
      nums[j] = nums[i];
      nums[i] = temp; 
    };
    int n = nums.size(); 
    for(int i = 0; i < n; i++) {
      while(nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
        int j = nums[i] - 1;
        swap(i, j);
      }
    }
    for(int i = 0; i < n; i++) {
      if(nums[i] != i + 1)
        return i + 1;
    }
    return n + 1;
  }
};