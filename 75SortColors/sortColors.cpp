#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int size = nums.size();
        int i = 0, j = 0;
        while(j < size) {
            if(nums[j] == 0) {
                swap(nums[i], nums[j]);
                i++;
            }
            j++;
        }
        j = i;
        while(j < size) {
            if(nums[j] == 1) {
                swap(nums[i], nums[j]);
                i++;
            }
            j++;
        }
    }
};

/**
 * 多指针单遍遍历
 * [0, i)是0的区域  [i, j)是1的区域
 * (n, size - 1]是2的区域
 * 
 * 0 1同向双指针的维护有点门道，
 * 加上n之后的相向指针走法和快排相向双指针有点像
 */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int size = nums.size();
        int i = 0, j = 0, n = size - 1, k = 0;
        while(k <= n) {
            if(nums[k] == 0) {
                nums[j] = 1; //先赋1后赋0，兼容i，j重合的情况
                j++;
                nums[i] = 0;
                i++;
            } else if(nums[k] == 1) {
                nums[j] = 1;
                j++;
            } else if(nums[k] == 2) {
                swap(nums[n], nums[k]);
                n--;
                continue;
            }
            k++;
        }
    }
};

/**
 * 0x3f的解法：反正安排完0和1之后剩下的应该全部是2，所以直接放上2了
 * 至于分区思想是一样的，对于同时维护0，1同向双指针的方法也是一样的
 */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0 = 0, p1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            int x = nums[i];
            nums[i] = 2;
            if (x <= 1) {
                nums[p1++] = 1;
            }
            if (x == 0) {
                nums[p0++] = 0;
            }
        }
    }
};

