#include <stack>
#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * 递归写法
 */
class Solution1 {
public:
  TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr) return nullptr;
    invertTree(root->left);
    invertTree(root->right);
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    return root;
  }
};

/**
 * 递归写法2
 */
class Solution2 {
public:
  TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr) return nullptr;
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    invertTree(root->left);
    invertTree(root->right);
    return root;
  }
};
/**
 * 迭代写法, 模拟递归写法2的栈调用，但并未完全模拟栈
 */
class Solution3 {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        std::stack<TreeNode*> stack;
        stack.push(root);
        while (!stack.empty()) {
            TreeNode* node = stack.top();
            stack.pop();
            if (node->left != nullptr) stack.push(node->left);
            if (node->right != nullptr) stack.push(node->right);
            TreeNode* tmp = node->left;
            node->left = node->right;
            node->right = tmp;
        }
        return root;
    }
};

#define WHITE 0
#define GRAY  1
#define BLACK 2
/**
 * 模仿递归写法1的函数栈
 * 迭代写法，用stack模拟函数的递归调用栈，用颜色代表该节点的函数栈的运行进度
 * 白色代表首次把这个节点入栈，对应递归中以该结点为参数的函数刚被调用
 * 灰色代表 invertTree(root->left) 已经返回了，该把该节点的右子节点入栈了
 * 黑色代表 invertTree(root->right) 已经返回了，该交换节点了
 */
class Solution {
public:
  struct ColorNode {
    TreeNode* node;
    int color;
    ColorNode() {}
    ColorNode(TreeNode* n, int c) : node(n), color(c) {}
  };

  TreeNode* invertTree(TreeNode* root) {
    std::stack<ColorNode> stk;
    stk.push(ColorNode(root, WHITE));
    while(!stk.empty() && stk.top().node != nullptr) {
      ColorNode& cur = stk.top();
      if(cur.color == WHITE) {
        cur.color = GRAY;
        if(cur.node->left != nullptr) 
          stk.push(ColorNode(cur.node->left, WHITE));
      } else if(cur.color == GRAY) {
        cur.color = BLACK;
        if(cur.node->right != nullptr) 
          stk.push(ColorNode(cur.node->right, WHITE));
      } else {
        TreeNode* temp = cur.node->left;
        cur.node->left = cur.node->right;
        cur.node->right = temp; 
        stk.pop();
      }
    }
    return root;
  }
};

int main() {
  std::stack<Solution::ColorNode> stk;
  stk.push(Solution::ColorNode(nullptr, WHITE));
  stk.top().color = BLACK;
  if(stk.top().color == BLACK) std::cout << "black" << std::endl;
  else std::cout << "white" << std::endl;
  int a = 3;
  int& b = a;
  int& c = b;
  c = 4;
  std::cout << a << std::endl;
}
