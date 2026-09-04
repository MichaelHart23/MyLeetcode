#include <bits/stdc++.h>
using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

/**
 * 20260904
 * 在每次构建一个四叉的时候, 都需要全图扫描一遍, 最差情况需要把整个二维数组扫描log2 n遍
 * 假设是一个n × n的数组, 2^m = n, 那么最差情况扫描 m 遍
 * 或许可以用一种启发性的方法
 * 哦, 不对, 只要扫描到0, 1混合就可以停止扫描了, 所以不会发生那么多扫描
 */
class Solution {
    enum {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
    struct Area {
        int left, right, top, bottom;
        Area() : left(0), right(0), top(0), bottom(0) {}
        Area(int l, int r, int t, int b) : left(l), right(r), top(t), bottom(b) {}
        Area subArea(int area) {
            switch (area) {
            case TOP_LEFT:
                return Area(left, (left + right) / 2, top, (top + bottom) / 2);
                break;
            case TOP_RIGHT:
                return Area((left + right) / 2 + 1, right, top, (top + bottom) / 2);
                break;
            case BOTTOM_LEFT:
                return Area(left, (left + right) / 2, (top + bottom) / 2 + 1,  bottom);
                break;
            case BOTTOM_RIGHT:
                return Area((left + right) / 2 + 1, right, (top + bottom) / 2 + 1, bottom);
                break;
            default: // not reach
                return Area();
                break;
            }
        }
    };
    int scanArea(vector<vector<int>>& grid, Area area) {
        bool allone = true, allzero = true;
        // 这里要尤为注意, left - right是列范围, top-bottom是行范围, 所以要先遍历top down, 后遍历left right
        for (int i = area.top; i <= area.bottom; i++) {
            for (int j = area.left; j <= area.right; j++) {
                if (grid[i][j] == 0) {
                    allone = false;
                } else {  // grid[i][j] == 1
                    allzero = false;
                }
                if (!allone && !allzero) {
                    return -1;
                }
            }
        }
        return allone ? 1 : 0;
    }
    // The semantic of the recursive function: return the sub quad tree of this area
    Node* quadTree(vector<vector<int>>& grid, Area area) {
        int res = scanArea(grid, area);
        if (res != -1) {
            return new Node(res, true);
        }
        Node* node = new Node(0, false);
        node->topLeft = quadTree(grid, area.subArea(TOP_LEFT));
        node->topRight = quadTree(grid, area.subArea(TOP_RIGHT));
        node->bottomLeft = quadTree(grid, area.subArea(BOTTOM_LEFT));
        node->bottomRight = quadTree(grid, area.subArea(BOTTOM_RIGHT));
        return node;
    }
public:
    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();
        return quadTree(grid, Area(0, n-1, 0, n-1));
    }
};
