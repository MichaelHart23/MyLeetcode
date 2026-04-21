#include <bits/stdc++.h>

using namespace std;

/**
 * 一行一行的遍历，遍历到其中一行的时候，已有信息是经过上一行的每个元素的最小路径和
 * 那经过该行的每个元素的最小路径也就有了
 * 
 * 这是自上向下遍历
 * 
 * 其实无论是自上向下遍历还是自下向上遍历，最重要的都是想到要计算经过某一行每个节点的最小路径和
 * 而不是把自己的思维限定在截止到某一行为止，最小路径和。这样会丢失信息
 */
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int rows= triangle.size();
        vector<int> minPath(rows, INT32_MAX); //当遍历到第n行的时候，minPath[i]表示经过该元素的最小路径和
        minPath[0] = triangle[0][0]; //第一行：归纳奠基
        for(int row = 1; row < rows; row++) { //从第二行遍历到尾
            int num = row + 1; //该行有多少元素
            int temp1 = minPath[0]; //记录临时变量
            int temp2 = minPath[num - 2]; //单独记录下来，可能minPath[num - 2]和minPath[0]同一个元素
            //单独更新头尾
            minPath[0] += triangle[row][0];
            minPath[num - 1] = temp2 + triangle[row][num - 1];
            //更新中间
            for(int i = 1; i < num - 1; i++) {
                temp2 = minPath[i];
                minPath[i] = min(temp1, temp2) + triangle[row][i];
                temp1 = temp2;
            }
        }
        int ans = INT32_MAX;
        for(int i : minPath) ans = min(ans, i);
        return ans;
    }
};

/**
 * 0x3f的自下向上遍历
 */
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int rows= triangle.size();
        vector<int> minPath(rows, INT32_MAX); //当遍历到第n行的时候，minPath[i]表示经过该元素的最小路径和
        for(int i = 0; i < rows; i++) {
            minPath[i] = triangle[rows - 1][i];
        }
        for(int row = rows - 2; row >= 0; row--) {
            int num = row + 1;
            for(int i = 0; i < num; i++) {
                minPath[i] = min(minPath[i], minPath[i + 1]) + triangle[row][i];
            }
        }
        return minPath[0];
    }
};
