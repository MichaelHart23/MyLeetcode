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




void printArray(vector<int>& vec) {
  for(int i : vec) {
    cout << i << " ";
  }
  cout << endl;
}

/**
 * 第一想法，有错，只能判断父子节点的关系，无法判断祖孙节点的关系
 * 递归还是可以实现的，给每个节点一个范围区间
 */
class Solution {
public:
  bool isValidBST(TreeNode* root) {
    if(root == nullptr) return true;
    bool res = true;
    if(root->left) {
      res &= root->left->val < root->val && isValidBST(root->left);
    }
    if(root->right) {
      res &= root->val < root->right->val && isValidBST(root->right);
    }
    return res;
  }
};


/**
 * 中序遍历，判断中序遍历的结果是否是递增的
 */
#define WHITE 0
#define GRAY  1

class Solution {
public:
  struct ColorNode {
    TreeNode* node;
    int color;
    ColorNode(TreeNode* node, int color) : node(node), color(color) {}
  };


  bool isValidBST(TreeNode* root) {
    vector<int> vec;
    stack<ColorNode> stk;
    stk.push(ColorNode(root, WHITE));
    TreeNode* cur = root;
    while(!stk.empty()) {
      ColorNode& node = stk.top();
      if(node.color == WHITE) {
        node.color = GRAY;
        if(node.node->left) stk.push(ColorNode(node.node->left, WHITE));
      } else {
        stk.pop();
        vec.push_back(node.node->val);
        if(node.node->right) stk.push(ColorNode(node.node->right, WHITE));
      }
    }
    for(int i = 1; i < vec.size(); i++) {
      if(vec[i - 1] >= vec[i]) return false;
    }
    return true;
  }
};


class Solution {
public:
  bool isValidBST(TreeNode* root, long long lower = LLONG_MIN, long long upper = LLONG_MAX) {
    if(root == nullptr) return true;
    if(root->val <= lower || root->val >= upper) return false;
    return isValidBST(root->left, lower, root->val) && isValidBST(root->right, root->val, upper);
  }
};

int main() {
  TreeNode* root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);
  Solution s;
  s.isValidBST(root);
}

