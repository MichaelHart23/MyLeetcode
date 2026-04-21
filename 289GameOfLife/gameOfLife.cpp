#include <bits/stdc++.h>

using namespace std;

/**
 * 周围八个格子有2或3个live cell则该cell存活，其余情况该cell都死亡
 */
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int dx[8] = {-1,  0, 1, 1, 1, 0, -1, -1};
        int dy[8] = {-1, -1,-1, 0, 1, 1,  1, 0};
        int rows = board.size(), cols = board[0].size();
        for(int row = 0; row < rows; row++) {
            for(int col = 0; col < cols; col++) {
                int num = 0;
                for(int i = 0; i < 8; i++) {
                    int x = row + dx[i], y = col + dy[i];
                    if(x >= 0 && x < rows && y >= 0 && y < cols) {
                        num += board[x][y] & 1;
                    }
                }
                if((num == 2 && board[row][col] & 1) || num == 3) {
                    board[row][col] |= 0b10;
                }
            }
        }
        for(int row = 0; row < rows; row++) {
            for(int col = 0; col < cols; col++) {
                if(board[row][col] & 0b10) {
                    board[row][col] = 1;
                } else {
                    board[row][col] = 0;
                }
            }
        }
    }
};
