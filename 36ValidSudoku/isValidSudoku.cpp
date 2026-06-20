#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_map<char, int> num_tb;
        for (char c = '1'; c <= '9'; c++) {
            num_tb[c] = 1;
        }
        auto dealAChar = [](unordered_map<char, int>& tb, char c) -> bool {
            if (c != '.') {
                if (--tb[c] < 0) {
                    return false;
                }
            }
            return true;
        };
        for (int row = 0; row < 9; row++) {
            auto tb_cp = num_tb;
            for (int col = 0; col < 9; col++) {
                if (!dealAChar(tb_cp, board[row][col])) {
                    return false;
                }
            }
        }

        for (int col = 0; col < 9; col++) {
            auto tb_cp = num_tb;
            for (int row = 0; row < 9; row++) {
                if (!dealAChar(tb_cp, board[row][col])) {
                    return false;
                }
            }
        }

        cout << "行列检查通过\n";

        auto dealABlock = [&](unordered_map<char, int>& tb, int r, int c) -> bool {
            for (int row = r; row < r + 3; row++) {
                for (int col = c; col < c + 3; col++) {
                    if (!dealAChar(tb, board[row][col])) {
                        return false;
                    }
                }
            }
            return true;
        };
        // 一开始，我误解成了每一个3*3的小方格都要满足条件

        // for (int row = 0; row < 7; row++) {
        //     auto tb_cp = num_tb;
        //     if (!dealABlock(tb_cp, row, 0)) {
        //         cout << "初始化block阶段: " << row << endl;
        //         return false;
        //     }
        //     for (int col = 3; col < 9; col++) {
        //         for (int r = row; r < row + 3; r++) {
        //             char c = board[r][col - 3];
        //             if (c != '.') {
        //                 tb_cp[c]++;
        //             }
        //         }
        //         for (int r = row; r < row + 3; r++) {
        //             if (!dealAChar(tb_cp, board[r][col])) {
        //                 cout << "block移动阶段: " << r << " " << col << endl;
        //                 return false;
        //             }
        //         }
        //     }
        // }
        for (int row = 0; row < 9; row += 3) {
            for (int col = 0; col < 9; col += 3) {
                auto tb_cp = num_tb;
                if (!dealABlock(tb_cp, row, col)) {
                    return false;
                }
            }
        }
        return true;
    }
};

// 一次遍历写法
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool row_has[9][9]{};         // row_has[i][x] 表示 i 行是否有数字 x
        bool col_has[9][9]{};         // col_has[j][x] 表示 j 列是否有数字 x
        bool sub_box_has[3][3][9]{};  // sub_box_has[i'][j'][x] 表示 (i',j') 宫是否有数字 x

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char b = board[i][j];
                if (b == '.') {
                    continue;
                }
                int x = b - '1';                                                       // 字符 '1'~'9' 转成数字 0~8
                if (row_has[i][x] || col_has[j][x] || sub_box_has[i / 3][j / 3][x]) {  // 重复遇到数字 x
                    return false;
                }
                // 标记行、列、宫包含数字 x
                row_has[i][x] = col_has[j][x] = sub_box_has[i / 3][j / 3][x] = true;
            }
        }

        return true;
    }
};