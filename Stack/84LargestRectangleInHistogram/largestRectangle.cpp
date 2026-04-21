#include <bits/stdc++.h>

using namespace std;

/**
 * 一开始的想法是选两个元素作为边界吗，枚举：O(n^2)的复杂度
 * 以每个元素作为左边界，枚举右边界，找到最大值
 * 怎么剪枝呢？换句话说，怎么知道以某个元素为左边界，不可能是最大值呢？
 * 该元素的高度 <= 其左边的元素的高度
 * 
 * 还能怎么优化呢？
 * 从更高的元素开始遍历吗？
 * 
 * 从一开始这个思路从O(n^2)优化，即使剪枝了，还是n^2这个数量级
 */
class Solution1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size(), res = 0;
        deque<int> dq; //所有可能的左边界, 即比左边高的元素
        dq.push_back(0);
        for(int i = 1; i < size; i++) {
            if(heights[i] > heights[i - 1]) 
                dq.push_back(i);
        }
        while(!dq.empty()) {
            int i = dq.front();
            dq.pop_front();
            res = max(res, heights[i]);
            int minHeight = heights[i];
            for(int j = i + 1; j < size; j++) {
                minHeight = min(minHeight, heights[j]);
                int maxArea = (size - i) * minHeight; //以i为左边界，且包括j，所能达到的最大面积
                if(maxArea <= res) break;  //剪枝
                int area = (j - i + 1) * minHeight;
                res = max(res, area);
            }
        }
        return res;
    }
};

/**
 * O(n)复杂度的解法
 * 最大矩形面积的高度一定是某个元素的高度
 * 洞察到这一点，就有了O(n)复杂度的地基，而不是枚举每个可选的area
 * 那遍历每个元素，算出以每个元素的高度为高度的最大面积矩形，取它们的最大值就好了
 * 以元素i的高度为高的最大面积矩形，找到i左右两边第一个小于heights[i]的元素
 * 
 * 三次遍历解法：
 */
class Solution2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        vector<int> preLess(size, -1); //-1表示左边没有比它更小的元素
        stack<int> stk;
        stk.push(0);
        //单调递增栈
        for(int i = 1; i < size; i++) {
            if(heights[i] > heights[i - 1]) { //大于左边的，找到目标了
                preLess[i] = i - 1;
            } else {
                while(!stk.empty() && heights[i] <= heights[stk.top()]) {
                    stk.pop(); 
                }
                if(!stk.empty()) preLess[i] = stk.top();
            }
            stk.push(i);
        }
        vector<int> nextLess(size, size); //size表示右边没有比它更小的数了
        stack<int> st;
        st.push(0);
        //单调递增栈
        for(int i = 1; i < size; i++) {
            if(heights[i] >= heights[st.top()]) {
                st.push(i);
            } else {
                while (!st.empty() && heights[i] < heights[st.top()]) {
                    nextLess[st.top()] = i;
                    st.pop();
                }
                st.push(i);
            }
        }
        int res = 0;
        for(int i = 0; i < size; i++) {
            int height = heights[i];
            int width = nextLess[i] - preLess[i] - 1;
            res = max(res, height * width);
        }
        return res;
    }
};

/**
 * 注意到二者都是单调递增栈，故得到两个数组的循环可以合并，等于的情况要额外留意一下
 * 当两个相等元素在碰到一起时——也即一个是栈顶元素，一个是遍历到的元素，只有两种情况：
 * 1 两者本来在数组中就挨在一起
 * 2 两者直接的元素比两者都大
 * 以上两种情况的每一种，以任意一者的高度为矩形高所得到的最大面积都是一样的，所以可以选择：
 * 牺牲其中一个，另一个不变
 * 
 * 两次遍历写法:
 */
class Solution3 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size(), res = 0;
        vector<int> preLess(size, -1); //-1表示左边没有比它更小的元素
        vector<int> nextLess(size, size); //size表示右边没有比它更小的数了
        stack<int> stk;
        stk.push(0);
        //单调递增栈
        for(int i = 1; i < size; i++) {
            //在这里处理等于情况也可以，不过栈中会同时存在两个相等元素，不是严格单调增了
            if(heights[i] > heights[stk.top()]) { //大于左边的，找到目标了
                preLess[i] = i - 1;
            } else if(heights[i] <= heights[stk.top()]) { //这里处理了等于的情况
                while(!stk.empty() && heights[i] < heights[stk.top()]) {
                    nextLess[stk.top()] = i;
                    stk.pop(); 
                }
                if(!stk.empty()) preLess[i] = stk.top();
            }
            //无论怎样该数都是要入栈的
            stk.push(i);
        }
        //一种更简洁的写法：
        // stack<int> stk;
        // for(int i = 0; i < size; i++) {
        //     while(!stk.empty() && heights[i] <= heights[stk.top()]) {
        //         nextLess[stk.top()] = i;
        //         stk.pop();
        //     }
        //     if(!stk.empty() && stk.top() > heights[i]) {
        //         preLess[i] = stk.top();
        //     }
        //     stk.push(i);
        // }
        
        for(int i = 0; i < size; i++) {
            int height = heights[i];
            int width = nextLess[i] - preLess[i] - 1;
            res = max(res, height * width);
        }
        return res;
    }
};

/**
 * 当遍历到一个不满足单调递增性元素i时，假设栈顶的元素是j，nextLess[j] = i;
 * 那preLess[j]是谁？是j在栈中的上一个元素，早已经被存到preLess数组中了，所以此时可以查到
 * 不过可以不要preLess[j]数组了，因为不借助这个数组也能找到preLess[j]
 * 也不要nextLess数组了，因为不借助这个数组也能达到目的
 * 
 * 那碰到相等的情况怎么办？和上面是一样的
 * 
 * 一次遍历写法：
 */
class Solution4 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size(), res = 0;
        stack<int> stk;
        for(int i = 0; i < size; i++) {
            while(!stk.empty() && heights[i] <= heights[stk.top()]) {
                int top = stk.top();
                stk.pop();
                int left = stk.empty() ? -1 : stk.top();
                res = max(res, heights[top] * (i - left - 1));
            }
            stk.push(i);
        }
        while(!stk.empty()) {
            int top = stk.top();
            stk.pop();
            int left = stk.empty() ? -1 : stk.top();
            res = max(res, (size - left - 1) * heights[top]);
        }
        return res;
    }
};


/**
 * 注意到上述写法中需要频繁根据stk是否为空来判断左边界是否是-1
 * 不如直接在栈底放一个哨兵-1
 * 同时注意到要写两个循环，第二个循环把栈清空，可以在原数组末尾加一个-1来把栈清空
 * 此时右边界也是正确的: 原数组的大小：size
 */
class Solution5 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size(), res = 0;
        heights.push_back(-1);
        stack<int> stk;
        stk.push(-1);
        for(int i = 0; i <= size; i++) {
            while(stk.top() != -1 && heights[i] <= heights[stk.top()]) {
                int top = stk.top();
                stk.pop();
                res = max(res, heights[top] * (i - stk.top() - 1));
            }
            stk.push(i);
        }
        return res;
    }
};
int main() {
    vector<int> h = {2, 1, 5, 6, 2, 3};
    Solution5 s;
    s.largestRectangleArea(h);
}
