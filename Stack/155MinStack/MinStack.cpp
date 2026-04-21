#include <bits/stdc++.h>

using namespace std;

/**
 * 给你一个数组 nums，如何计算每个前缀的最小值？

定义 preMin[i] 表示 nums[0] 到 nums[i] 的最小值。

这可以从左到右计算：

preMin[0]=nums[0]。
preMin[1]=min(nums[0],nums[1])。
preMin[2]=min(nums[0],nums[1],nums[2])=min(preMin[1],nums[2])。
preMin[3]=min(nums[0],nums[1],nums[2],nums[3])=min(preMin[2],nums[3])。
……
一般地，我们有

preMin[i]=min(preMin[i−1],nums[i])
 */
class MinStack {
private:
    vector<pair<int, int>> stack; //第一个元素存元素本身，第二个元素存自底向上的最小值
public:
    MinStack() {
        //栈底哨兵，处理第一次push时，不用特判是否栈空
        stack.emplace_back(0, INT32_MAX);
    }
    
    void push(int val) {
        stack.emplace_back(val, min(getMin(), val));
    }
    
    void pop() {
        stack.pop_back();
    }
    
    int top() {
        return stack.back().first;
    }
    
    int getMin() {
        return stack.back().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */