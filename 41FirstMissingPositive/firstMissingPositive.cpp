#include <algorithm>
#include <vector>

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
        for (int i = 0; i < n; i++) {
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
    }
};

/**
 * 20260429重做，和上面思路一样，原地哈希：
 * 把数字放到其对应下标上去，考虑重复数字
 */
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size(), ans  = -1;
        for(int i = 0; i < n; i++) {
            while(nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for(int i = 0; i < n; i++) {
            if(nums[i] != i + 1) {
                ans = i +  1;
                break;            
            }
        }
        return ans == -1 ? n + 1 : ans;
    }
};