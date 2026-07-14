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
 * 20260714
 * 优化方向：1 用span简化代码；2 用map加快查找
 */
class Solution {
    TreeNode* buildTreeHelper(vector<int>& inorder, int inLeft, int inRight, vector<int>& postorder, int postLeft, int postRight) {
        if (inLeft > inRight) {
            return nullptr;
        }
        if (inLeft == inRight) {
            return new TreeNode(inorder[inLeft]);
        }
        int rootVal = postorder[postRight];
        int rootIndexIn;
        for (int i = inLeft; i <= inRight; i++) {
            if (inorder[i] == rootVal) {
                rootIndexIn = i;
                break;
            }
        }
        int leftTreeLen = rootIndexIn - inLeft;
        TreeNode* root = new TreeNode(rootVal);
        root->left = buildTreeHelper(inorder, inLeft, rootIndexIn - 1, postorder, postLeft, postLeft + leftTreeLen - 1);
        root->right = buildTreeHelper(inorder, rootIndexIn + 1, inRight, postorder, postLeft + leftTreeLen, postRight - 1);
        return root;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() == 0) return nullptr;
        return buildTreeHelper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
};