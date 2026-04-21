#include <bits/stdc++.h>

using namespace std;


/**
 * 维护一个从当前格子能一步到达的最远距离
 * 以及一个到当前位置所需要的最小步数的数组
 * 
 * 还有时间复杂度更低的解法
 */
class Solution {
public:
    int jump(vector<int>& nums) {
        int size = nums.size(), farthest = 0;
        if(size <= 1) return 0; 
        vector<int> steps(size, INT32_MAX);
        steps[0] = 0;
        for(int i = 0; i < size; i++) {
            farthest = nums[i] + i;
            if(farthest >= size - 1) { //从当前位置可以到头，可以直接返回了，不用继续往下找了，相当于一个剪枝
                return steps[i] + 1;
            }
            for(int j = i + 1; j < size && j <= farthest; j++) {
                steps[j] = min(steps[j], steps[i] + 1);
            }
        }
        return steps[size - 1];
    }
};

/**
 * 贪心起来：
 * 最左边的能一步到终点的节点就是最短路径的最后一步
 * 再把这个节点作为终点，找最左边的能一步到它自己的
 * 
 * 实际上和上面的方法差不多，都到不了O(n)的复杂度
 */


class Solution {
public:
    int jump(vector<int>& nums) {
        int size = nums.size(), ans = 1;
        if(size <= 1) return 0;
        int curRight = nums[0];
        int farthest = 0;
        for(int i = 0; i < size; i++) {
            farthest = max(farthest, nums[i] + i);
            if(i == size - 1) break;
            if(i >= curRight) {
                ans++;
                curRight = farthest;
                if(curRight >= size - 1) break;
            }
        }
        return ans;
    }
};
