#include <bits/stdc++.h>

using namespace std;

/**
 * 20260716
 * 假设每个位置都有一个编号，那梯子是传送到编号更大的地方；即往前走，蛇是传送到编号更小的地方，即往后退
 * 完全可以把场景抽象/简化为一维路径，n^2个点，有传送门
 * 我的第一思路是dp，计算出到达每个位置所需的最少步数，状态转换方程涉及前六个位置以及到达该位置的传送门
 * 但后向传送门似乎会打乱/干扰dp
 * 后向传送门唯一有用的地方是和两个交叉的前向传送门交叉
 * dp方法是：碰到一个传送门就开一个递归沿这个传送门走到头
 * 我能否证明这种做法是正确的呢？
 * 
 * 说是有BFS做法，BFS怎么做？
 * 20260731
 * 枚举走一步后有哪些可能的结果，走两步后有哪些可能的结果。指数级增长
 */
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        // 把二维图转化为一维
        vector<int> list(n * n + 1, -1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != -1) {
                    int a = n - i; // 自下向上第a行
                    int b = j + 1; // 自左到右第b列
                    // 计算当前位置的序号
                    int num = (a - 1) * n;
                    num += a % 2 != 0 ? b : n - b + 1;
                    list[num] = board[i][j];
                }
            }
        }
        deque<int> que; // 当前的步数能到达哪些位置
        que.push_back(1);
        vector<bool> reached(n * n + 1, false);
        reached[1] = true;
        int steps = 0;
        while (!que.empty()) {
            steps++;
            deque<int> newQue;
            for (int i : que) {
                for (int j = 1; j <= 6; j++) {
                    int pos = 0;
                    if (list[i + j] != -1) {
                        pos = list[i + j];
                    } else {
                        pos = i + j;
                    }
                    if (reached[pos]) {
                        continue;
                    }
                    reached[pos] = true;
                    newQue.push_back(pos);
                    if (pos == n * n) {
                        return steps;
                    }
                }
            }
            que = std::move(newQue);
        }
        return -1;
    }
};
