#include <bits/stdc++.h>

using namespace std;

/**
 * 要找到下一个字典序的排列，那肯定是改越低位的越好
 * 从后往前遍历，从后往前升序的部分不懂，一旦找到一个下降的元素，将他和升序序列中最小的大于它的元素交换
 * 交换完之后把原从后往前的升序序列反转，相当于把能改的最低位变大之后，把基于该最低位的尾部变为最小
 * 
 * 若是遍历完发现整个序列是升序序列，那就整体反转
 */
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int size = nums.size();
        auto flip = [&](int left, int right) {
            for(int i = left, j = right; i < j; i++, j--) {
                swap(nums[i], nums[j]);
            }
        };
        for(int i = size - 1; i > 0; i--) {
            //如果从后往前是升序的，那升序的部分没有优化空间了
            if(nums[i] > nums[i - 1]) {
                for(int j = size - 1; j >= i; j--) {
                    if(nums[j] > nums[i - 1]) {
                        swap(nums[j], nums[i - 1]);
                        flip(i, size - 1);
                        return;
                    }
                }
            } 
        }
        flip(0, size - 1);
    }
};
