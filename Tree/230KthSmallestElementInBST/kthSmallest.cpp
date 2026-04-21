#include <vector>
#include <iostream>
#include <stack>

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
 * 中序遍历BST，遍历到第k个节点返回
 * 每当一个节点入栈时，下一次遍历就相当于到了以该结点为参数的函数栈
 */
class Solution {
public:
  int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> stk;
    while(!stk.empty() && root != nullptr) {
      if(root != nullptr) { 
        stk.push(root);
        root = root->left;
      } else {
        if(--k == 0) return stk.top()->val;
        root = stk.top()->right;
        stk.pop();
      }
    }
    return -1;
  }
};
