#include <bits/stdc++.h>

using namespace std;


/**
 * 20260715
 * 当做到这个题的时候，我第一想法是用一个递归式的搜索，之后我想到一个问题，当碰壁的时候，这个碰壁的信息能否
 * 传达到所有连通图的节点？如果不能，就要维护这个连通图的一些元信息来知道这个连通图是否碰壁
 * 之后我对深搜进行了一次手动模拟，我发现深搜的递归深度等于连通图的节点数，所以是可以把这个是否碰壁的信息传递
 * 下去，并返回上去来做到所有连通图节点共享是否碰壁这一信息
 * 但既然是要共享信息，直接整一个全局变量不就好
 * 
 * 另外的思考：似乎递归只能实现深搜，广搜需要迭代和队列
 */
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        // 顺序是：右，下，左，上。有讲究的
        // 由于原点位于左上角，且x代表行，y代表列，所以x实际上影响的是纵坐标，y实际影响的是横坐标
        int dr[4] = {0, 1, 0, -1};
        int dc[4] = {1, 0, -1, 0};
        int rows = board.size();
        int cols = board[0].size();
        bool touchEdge = false;
        auto dfs = [&](this auto&& dfs, int row, int col) {
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
                touchEdge = true;
                return;
            }
            if (board[row][col] != 'O') {
                return;
            }
            // 给这个位置打一个标记，说明这个位置已经处理过了；并且如果这个位置没有被写为X的话，会被重新写为0
            board[row][col] = '1';
            for (int i = 0; i < 4; i++) {
                dfs(row + dr[i], col + dc[i]);
            }
            // 由于深搜的特点，所有的节点都会在这里正确的设置自身
            if (!touchEdge) board[row][col] = 'X';
        };
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (board[row][col] == 'O') {
                    touchEdge = false;
                    dfs(row, col);
                }
            }
        }
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (board[row][col] == '1') {
                    board[row][col] = 'O';
                }
            }
        }
    }
};
/**
 * X O X
 * X O X
 * X X X
 * 以上写法处理不了这种情况，触边发生在一开始，深搜搜不到触边
 * 解决：没必要从边开始深搜，因为边上的O及其对应的连通图一定是触边的
 * 但在这种情况下
 * X X X X O X X X
 * X O O O O O O X
 * X X X X X X X X
 * 由于是优先往右搜，所以也会有问题
 * 深搜的递归深度等于连通图的节点数这个结论不对
 * 还是需要一种，等全部搜索结束之后再赋值的方法，
 * 那就需要一种能表示连通图都包含哪些节点的数据结构
 * 或者深搜两遍
 * 或者有一个trick，只从边上的O开始搜，把从边上的O能搜到的O标记，这些O就是不能被写为X的O，其余的所有O都是能被写为X的O
 */
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        // 顺序是：右，下，左，上。有讲究的
        // 由于原点位于左上角，且x代表行，y代表列，所以x实际上影响的是纵坐标，y实际影响的是横坐标
        int dr[4] = {0, 1, 0, -1};
        int dc[4] = {1, 0, -1, 0};
        int rows = board.size();
        int cols = board[0].size();
        auto dfs = [&](this auto&& dfs, int row, int col) {
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
                return;
            }
            if (board[row][col] != 'O') {
                return;
            }
            // 给这个位置打一个标记，说明这个位置已经处理过了, 是能从边上的O搜到的O
            board[row][col] = '1';
            for (int i = 0; i < 4; i++) {
                dfs(row + dr[i], col + dc[i]);
            }
        };
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                bool isEdge = row == 0 || col == 0 || row == rows - 1 || col == cols - 1;
                if (isEdge && board[row][col] == 'O') {
                    dfs(row, col);
                }
            }
        }
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (board[row][col] == '1') {
                    board[row][col] = 'O';
                } else if (board[row][col] == 'O') {
                    board[row][col] = 'X';
                }
            }
        }
    }
};