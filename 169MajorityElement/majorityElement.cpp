#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = 0, hp = 0;
        for(int i : nums) {
            if(hp == 0) {
                res = i;
                hp = 1;
            } else {
                if(res == i) hp++;
                else hp--;
            }
        }
        return res;
    }
};
