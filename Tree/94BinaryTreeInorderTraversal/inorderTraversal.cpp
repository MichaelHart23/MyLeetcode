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
//正常递归遍历
class Solution {
public:
  void inorderTraversalHelper(vector<int>& vec, TreeNode* node) {
    if(node == nullptr) return;
    inorderTraversalHelper(vec, node->left);
    vec.push_back(node->val);
    inorderTraversalHelper(vec, node->right);
  }
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    inorderTraversalHelper(res, root);
    return res;
  }
};

// 不易理解的迭代遍历，差
class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> s;
    while(!s.empty() && root != nullptr) {
      while(root != nullptr) {
        s.push(root);
        root = root->left;
      }
      TreeNode* top = s.top();
      s.pop();
      res.push_back(top->val);
      root = top->right;
    }
    return res;
  }
};

/**
 * 符合直觉的迭代遍历，好
 * 很容易就能看出是在模拟递归遍历的栈 
 * 
 * cur指向一个节点，同时cur代表着以该节点为参数的函数栈，
 * 这一个个函数栈，放在了stack s里，当cur为空时，也就代表着一个函数栈的完结
 */
class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> s;
    TreeNode* cur = root;

    //cur指向一个节点，同时cur代表着以该节点为参数的函数栈
    while(!s.empty() || cur != nullptr) {
      if(cur != nullptr) {
        s.push(cur);  //当cur不为空时，代表着要进入某个函数栈
        cur = cur->left;
      } else {  //当cur为空时，代表着一个函数栈的结束
        TreeNode* top = s.top();
        s.pop();
        res.push_back(top->val);
        cur = top->right;
      }
    }
    return res;
  }
};

/**
 * Morris遍历，空间复杂度O(1)，时间复杂度O(n)
 * 线索树遍历
 */
class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ret;
    TreeNode* pre=nullptr;
    while(root!=nullptr){
      if(root->left!=nullptr){
        pre=root->left;//从root左子节点开始，一直往右循迹到最右子节点
        while(pre->right!=nullptr && pre->right!=root){
          pre=pre->right;
        }
        if(pre->right==nullptr){//如果最右子节点的右子节点为空，则与root建立联系，根节点往左移动
          pre->right=root;
          root=root->left;
        } else {//如果最右子节点的右子节点非空，说明之前已经与root建立了联系，是第二次访问，ret记录root值，同时root往上走两层
          ret.push_back(root->val);
          root=root->right;
          pre->right=nullptr;
        }
      } else {//如果root的左子节点为空，说明已经第二次回到最左边了，ret记录根值，同时root网上走两层
        ret.push_back(root->val);
        root=root->right;
      }
    }        
    return ret;
  }
};


#define WHITE 0
#define GRAY  1
/**
 * 我自己版本的颜色遍历法，和原作者的有些不一样
 * 原作者实际上是进行子树展开
 * 我这个还是对递归函数栈的模式，只不过用颜色判断节点什么时候该出栈
 */
class Solution {
public:
  struct ColorNode {
    TreeNode* node;
    int color;
    ColorNode(TreeNode* node, int color) : node(node), color(color) {}
  };

  vector<int> inorderTraversal(TreeNode* root) {
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
    return vec;
  }
};


