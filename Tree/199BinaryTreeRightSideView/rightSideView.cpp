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
 * 层序遍历BFS
 */
class Solution {
public:
  vector<int> rightSideView(TreeNode* root) {
    if(root == nullptr) return {};
    vector<int> res;
    vector<TreeNode*> stk;
    stk.push_back(root);
    while(!stk.empty()) {
      vector<TreeNode*> newStack;
      res.push_back(stk.front()->val);
      for(auto n : stk) {
        if(n->right) newStack.push_back(n->right);
        if(n->left) newStack.push_back(n->left);
      }
      stk = move(newStack);
    }
    return res;
  }
};

/**
 * DFS遍历
 */
class Solution {
public:
  void dfs(TreeNode* node, int depth, vector<int>& ans) {
    if(node == nullptr) return;
    if(depth == ans.size()) ans.push_back(node->val);
    dfs(node->right, depth + 1, ans);
    dfs(node->left, depth + 1, ans);

  }
  vector<int> rightSideView(TreeNode* root) {
    vector<int> ans;
    dfs(root, 0, ans);
    return ans;
  }
};
