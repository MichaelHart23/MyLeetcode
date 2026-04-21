#include <vector>

using namespace std;

class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    int j = 0;
    size_t size = nums.size();
    for(int i = 0; i < size; i++) {
      if(nums[i]) {
        if(j < i)
          nums[j] = nums[i];
        j++;
      }
    }

    // while(i < size) {
    //   if(nums[i] == 0) {
    //     i++;
    //     continue;
    //   } else {
    //     if(j < i) {
    //       nums[j] = nums[i];
    //     }
    //     j++;
    //     i++;
    //   }
    // }
    for(int i = j; i < size; i++) {
      nums[i] = 0;
    }
  }
};