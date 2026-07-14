#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {
    }
};

/**
 * 简单的分层层序遍历
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        deque<TreeNode*> que;
        vector<vector<int>> res;
        que.push_back(root);
        bool reverse = false;
        while (!que.empty()) {
            vector<int> level;
            if (reverse) {
                int size = que.size();
                for (int i = size - 1; i >= 0; i--) {
                    level.push_back(que[i]->val);
                }
            } else {
                for (auto node : que) {
                    level.push_back(node->val);
                }
            }
            res.push_back(std::move(level));
            reverse = !reverse;
            deque<TreeNode*> newQue;
            for (auto node : que) {
                if (node->left) newQue.push_back(node->left);
                if (node->right) newQue.push_back(node->right);
            }
            que = std::move(newQue);
        }
        return res;
    }
};