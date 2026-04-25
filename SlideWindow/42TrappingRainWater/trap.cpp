#include <bits/stdc++.h>

using namespace std;

// 从上到下一行一行算
class Solution1 {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        int left = 0, right = size - 1;
        while (left < size && height[left] == 0) left++;
        while (right >= 0 && height[right] == 0) right--;
        int res = 0;
        for (int i = left; i < right; i++) {            // 以第i个位置为左边界
            for (int j = height[i]; j > 0; j--) {       // 从该位置最高处到最低处的遍历
                for (int k = i + 1; k <= right; k++) {  // 为该高度寻找右边界
                    if (height[k] >= j) {
                        res += (k - i - 1);
                        break;
                    }
                }
            }
        }
        return res;
    }
};

// 单调栈的雏形，直接计算两个相对高的墙壁能围起多少水来
class Solution2 {
public:
    int calculate(vector<int>& height, int left, int right) {  // 计算left和right之间能围多少水
        int blocks = 0;
        for (int k = left + 1; k < right; k++) { blocks += height[k]; }
        return (right - left - 1) * std::min(height[left], height[right]) - blocks;
    }
    int trap(vector<int>& height) {
        int size = height.size();
        int left = 0, right = size - 1;
        while (left < size && height[left] == 0) left++;
        while (right >= 0 && height[right] == 0) right--;
        int res = 0;
        for (int i = left; i < right;) {  // 以i为最左边界
            int j = i + 1;
            int max_right = j;
            for (j = i + 1; j <= right; j++) {
                if (height[j] >= height[i]) {  // 能找到一个 >= 左边界高度的值
                    res += calculate(height, i, j);
                    i = j;
                    max_right = -1;
                    break;
                } else {
                    if (height[j] >= height[max_right]) { max_right = j; }
                }
            }
            if (max_right != -1) {  // 没能找到一个 >= 左边界高度的值
                res += calculate(height, i, max_right);
                i = max_right;
            }
        }
        return res;
    }
};

/**
 * 20260421重做写的题解：每个池子的蓄水量取决于它左边最高墙和右边最高墙的最小值
 */
class Solution3 {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        vector<int> preHigh(size, 0), nextHigh(size, 0);
        int pre = 0;
        for(int i = 0; i < size; i++) {
            preHigh[i] = pre;
            pre = max(pre, height[i]);
        }
        int next = 0;
        for(int i = size - 1; i >= 0; i--) {
            nextHigh[i] = next;
            next = max(next, height[i]);
        }
        int ans = 0;
        for(int i = 0; i < size; i++) {
            int minHigh = min(preHigh[i], nextHigh[i]);
            if(height[i] >= minHigh) continue;
            else ans += minHigh - height[i];
        }
        return ans;
    }
};

/**
 * 0x3f的单遍遍历双指针做法
 * 注意到在上面Solution3做做法中，我们并不是真的需要知道前缀最大值和后缀最大值，我们只需要知道二者其中
 * 较小的一个就好
 */


/**
 * 20260422重做写的题解：单调栈做法
 */
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size(), ans = 0;
        std::deque<int> stk;
        stk.push_back(0);
        for(int i = 1; i < size; i++) {
            if(height[i] < height[stk.back()]) {
                stk.push_back(i);
                continue;
            }
            int lastHigh = 0;
            while(!stk.empty() && height[i] >= height[stk.back()]) {
                lastHigh = stk.back();
                stk.pop_back();
            }
            int h = stk.empty() ? height[lastHigh] : height[i];
            int start = stk.empty() ? lastHigh + 1 : stk.back() + 1;
            for(int j = start; j < i; j++) {
                ans += h - height[j];
                height[j] = h;
            }
            stk.push_back(i);
        }
        return ans;
    }
};

int main() {
    vector<int> v = {4, 2, 0, 3, 2, 5};
    Solution s;
    s.trap(v);
}
