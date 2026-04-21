#include <bits/stdc++.h>

using namespace std;

//异或运算
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int i : nums) res ^= i;
        return res;
    }
};
