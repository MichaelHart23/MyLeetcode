#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int cur_element_count = 1;
        int num_forward = 0;
        int size = nums.size();
        int last_element = nums[0];
        for (int i = 1; i < size; i++) {
            if (nums[i] == nums[i - 1]) {
                cur_element_count++;
            } else {
                cur_element_count = 1;
            }
            if (cur_element_count > 2) {
                num_forward++;
            } else {
                nums[i - num_forward] = nums[i]; 
            }
        }
        return size - num_forward;
    }
};


class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        if (size <= 2) {
            return size;
        }
        int cur_size = 2;
        for (int i = 2; i < size; i++) {
            if (nums[i] != nums[cur_size - 2]) {
                nums[cur_size++] = nums[i];
            }
        }
        return cur_size;        
    }
};

