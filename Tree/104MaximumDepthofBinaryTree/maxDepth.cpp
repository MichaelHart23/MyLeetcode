#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 把子树的信息收集上来
 */
class Solution {
public:
  int maxDepth(TreeNode* root) {
    if(root == nullptr) {
      return 0;
    }
    int left_depth = maxDepth(root->left);
    int right_depth = maxDepth(root->right);
    return max(left_depth, right_depth) + 1;
  }
};

/**
 * 把父节点的信息传递下去
 */
class Solution {
public:
  /**
   * depth是当前node节点的父节点的深度，返回的是左右子树最深的那一颗的深度
   */
  int dfs(TreeNode* node, int depth) {
    if(node == nullptr) return depth;
    return max(dfs(node->left, depth + 1), dfs(node->right, depth + 1));
  }
  int maxDepth(TreeNode* root) {
    if(root == nullptr) return 0;
    return dfs(root, 0);
  }
};

/**
 * 层序遍历
 */
class Solution {
public:
  int maxDepth(TreeNode* root) {
    if(root == nullptr) return 0;
    vector<TreeNode*> que;
    int res = 0;
    que.push_back(root);
    while(!que.empty()) {
      vector<TreeNode*> tempQueue;
      for(auto node : que) {
        if(node->left != nullptr) {
          tempQueue.push_back(node->left);
        }
        if(node->right != nullptr) {
          tempQueue.push_back(node->right);
        }
      }
      res++;
      que = tempQueue;
    }
    return res;
  }
};



