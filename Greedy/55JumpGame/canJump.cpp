#include <bits/stdc++.h>

using namespace std;


/**
 * 关键在于0，如果有一个0怎么也越不过去，那么走不到头，反之能
 * 维护当前所能到达的最远地方，当碰到一个0的时候发现走不过去，那么就不能到达
 * 维护最右可达位置
 */
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size(), farthest = 0;
        for(int i = 0; i < size; i++) {
            farthest = max(farthest, nums[i] + i);
            if(nums[i] == 0 && farthest <= i) { //这个0可能是末尾的0，那能到达这个0实际上也算走到头了
                break;
            }
        }
        return farthest >= size - 1;
    }
};
