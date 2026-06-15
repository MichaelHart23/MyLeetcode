#include <bits/stdc++.h>
using namespace std;

/**
 * 很好的一道训练思维的题目，在不经过思考的情况下，肯定会想以每个station作为开始点尝试，这样是O(n^2)的复杂度
 * 想要减小复杂度，就要观察这个结构，思考这个结构，分析这个结构。最终发现这个结构的特殊之处，这就是算法题的重要意义之一吧
 * 你能处理的了更难的结构，能更快的处理结构，那解决问题的能力就越强
 *
 * 说回这道题目
 * 首先我对gas和cost做差，这样就是在每个节点上的净收获，题目要求就是从某个节点开始走一圈，净收获一直不为0
 * 在总正值 >= 总负值的情况下，一定存在答案吗？
 * 说实话，我并没有纯靠自己解决这个问题，这个结构最关键的一个点，我是被提示的
 * 那就是"负值的最值点"
 * 在总正值 >= 总负值 和 负值的最值点 的条件下，负值的最值点的下一个节点就是答案
 * 以下是基于这个洞察的证明
 * 1 从下一个节点出发，一直到边上，不会出现负值，如果出现负值，那么该点就是负值的最值点了，与假设矛盾
 * 2 从边上返回开头再走，也不会出现负值，因为负值的最值点已经发现了，那剩下的会累计足够多的正值，由于总正值大于等于总负值，所以累计的正值
 *   比负值的最值还要多，所以不会再出现负值
 *
 */
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // 由于闭包调用会降低性能，所以此处没有用闭包调用，但用闭包调用确实语义更明确，可读性更强
        // auto diff = [&](int i) -> int { return gas[i] - cost[i]; };
        int n = gas.size();
        int neg_max = 0, neg_max_index = 0, cur_gas = 0;
        for (int i = 0; i < n; i++) {
            cur_gas += gas[i] - cost[i];  // diff(i)
            if (cur_gas < neg_max) {
                neg_max = cur_gas;
                neg_max_index = i + 1;
            }
        }
        if (cur_gas < 0) {
            return -1;
        }
        return neg_max_index;
    }
};
