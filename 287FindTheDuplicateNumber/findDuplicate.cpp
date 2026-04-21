#include <bits/stdc++.h>

using namespace std;

/**
 * 利用元素范围的特殊性：[1, n], 而数组的大小是n + 1, 下标范围是[0, n]
 * 所以每一个元素都能找到与其相等的的下标
 * 
 * 利用上述思想的第一个方法：
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int ans = 0;
        //若某个下标被元素重复索引到，说明与这个下标相等的元素是重复元素
        for(int i : nums) {
            //以元素作为下标去索引，把被索引到的下标变为相反数，意思是和该下标相等的元素出现过了
            if(nums[abs(i)] < 0) { 
                ans = abs(i);
                break;
            } else {
                nums[abs(i)] *= -1;
            }
        }
        //恢复数组
        for(int& i : nums) {
            if(i < 0) i = -i;
        }
        return ans;
    }
};

/**
 * 继续根据以上性质，通过元素对于的下标，再通过该下标对于的元素索引下一个下标，
 * 由此可以形成一个图结构，这个图结构一定是有环的，因为它只能在数组里面打转转 
 * 而重复元素的存在，一定形成了一个环。也有可能存在多个环，但重复元素一定构成了一个环
 * 
 * 如果存在其他的环，那么该环是独立的环，外界进不来，环内元素也出不去
 * 独立的环的形成条件是：下标与元素是对用的，比如下标的范围是[m, n](0 < m <= n), 那么元素的范围是[m, n]
 * 这样便可以形成一个或多个独立的环，所以重复元素一定不可能全在独立的环内
 * 如果独立的环含有重复元素中的一个，那么该环就不再独立了，因为外界还有一个重复元素，可以借助该元素进入该环
 * 
 * 由于元素的范围只有[1, n], 而下标多了一个0, 所以从0可以看作图的入口，而从该入口出发一定到不了独立的环
 * 
 * 所以重复节点是环的入口，那找到环的入口就好了，和 142 detectCycle 的方法一样：Floyd判圈法
 */
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int ans = 0;
        int slow = 0, fast = 0;
        while(true) {
            slow = nums[slow];
            fast = nums[fast];
            fast = nums[fast];
            if(fast == slow) break;
        }
        while(ans != slow) {
            ans = nums[ans];
            slow = nums[slow];
        }
        return ans;
    }
};
