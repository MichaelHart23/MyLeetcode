#include <vector>
#include <iostream>
#include <stack>
#include <span>
#include <ranges>
#include <unordered_map>
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


class Solution {
  struct returnInfo {
    TreeNode* node;
    bool hasP; // p是否是node的descendant
    bool hasQ; // q是否是node的descendant
  };
  /**
   * 递归向下，记录每个节点是否是p或q，把这个信息保存在returnInfo结构体里返回
   * 向上回溯的时候，父节点看自身或左右子树中是否有p或q，若同时有了p和q，则第一次得到这个信息的
   * 节点就是LCA，自此一直把该returnInfo回溯向上
   * 
   * 一次遍历就能得到结果
   */
  returnInfo dfs(TreeNode* node, TreeNode* p, TreeNode* q) {
    if(node == nullptr) return {nullptr, false, false};
    returnInfo infoLeft = dfs(node->left, p, q);
    if(infoLeft.hasP && infoLeft.hasQ) return infoLeft;
    returnInfo infoRight = dfs(node->right, p, q);
    if(infoRight.hasP && infoRight.hasQ) return infoRight;
    returnInfo info;
    info.node = node;
    info.hasP = node == p || infoLeft.hasP || infoRight.hasP;
    info.hasQ = node == q || infoLeft.hasQ || infoRight.hasQ;
    return info;
  }
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return dfs(root, p, q).node;
  }
};


/**
 * 一个更简洁的实现
 * 问：为什么发现当前节点是 p 或者 q 就不再往下递归了？万一下面有 q 或者 p 呢？
 * 答：如果下面有 q 或者 p，那么当前节点就是最近公共祖先，直接返回当前节点。
 * 如果下面没有，那既然都没有要找的节点了，也不需要递归，直接返回当前节点。
 */
class Solution {
public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 找到 p 或 q 就不往下递归了
    if(root == nullptr || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left && right) { // 左右都找到
      return root; // 当前节点是最近公共祖先
    }
    // 如果只有左子树找到，就返回左子树的返回值
    // 如果只有右子树找到，就返回右子树的返回值
    // 如果左右子树都没有找到，就返回 nullptr（注意此时 right = nullptr）
    return left ? left : right;
    }


};
