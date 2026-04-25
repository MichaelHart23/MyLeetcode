#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        size_t size = nums.size();
        for (int i = 0; i < size; i++) {
            if (nums[i]) {
                if (j < i) nums[j] = nums[i];
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
        for (int i = j; i < size; i++) {
            nums[i] = 0;
        }
    }
};

/**
 * 20260424重做：记录每个元素前面有几个零，有几个就往前移动 n 位，最后填充末尾0
 */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zeroes = 0, size = nums.size();
        for(int i = 0; i < size; i++) {
            if(nums[i] == 0) {
                zeroes++;
                continue;
            }
            nums[i - zeroes] = nums[i];
        }
        for(int i = 0; i < zeroes; i++) {
            nums[size - i - 1] = 0;
        }
    }
};
