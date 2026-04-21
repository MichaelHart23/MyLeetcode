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

/**
 * 本题有两个关键概念：
 * 链：从下面的某个节点（不一定是叶子）到当前节点的路径。
 * 把这条链的节点值之和，作为 dfs 的返回值。如果节点值之和是负数，则返回 0（和 0 取最大值）。
 * 这个思想和 53. 最大子数组和 是一样的，如果左侧子数组的元素和是负数，就不和当前元素拼起来。
 * 
 * 直径：等价于由两条（或者一条）链拼成的路径。
 * 我们枚举每个 node，假设直径在这里「拐弯」，
 * 也就是计算由左右两条从下面的某个节点（不一定是叶子）到 node 的链的节点值之和，去更新答案的最大值。
 */
class Solution {
public: 
  unordered_map<TreeNode*, int> map;
  //找到以node为根节点的，单向下的最大路径和, 并利用哈希表存储结果，存储每个节点的最大路径和
  // 此函数的路径和的定义和题目的定义不一样，此函数的是以当前节点为根节点，单向下的最大路径和, 也即上述概念中的链和
  int findMaxBaseNode(TreeNode* node) {
    if(node == nullptr) return 0;
    int leftVal = findMaxBaseNode(node->left);
    int rightVal = findMaxBaseNode(node->right);
    int res;
    if(leftVal < 0 && rightVal < 0) res = node->val;
    else res = node->val + max(leftVal, rightVal);
    map[node] = res;
    return res;
  }
  int maxPathSum(TreeNode* root) {
    findMaxBaseNode(root);
    int res = INT_MIN;
    queue<TreeNode*> que;
    que.push(root);
    // 遍历每个节点，寻找经过每个节点的路径的最大值，找到这些最大值中的最大值
    while(!que.empty()) {
      TreeNode* node = que.front();
      que.pop();
      int sum = node->val;
      if(node->left) {
        que.push(node->left);
        if(map[node->left] > 0) sum += map[node->left];
      }
      if(node->right) {
        que.push(node->right);
        if(map[node->right] > 0) sum += map[node->right];
      }
      res = max(res, sum);
    }
    return res;
  }
};

/**
 * 可以通过一次遍历直接得出答案
 * 且不用哈希表
 */
class Solution {
public: 
  int ans;
  int dfs(TreeNode* node) {
    if(node == nullptr) return 0;
    int leftVal = dfs(node->left);
    int rightVal = dfs(node->right);
    int res = node->val;
    if(leftVal > 0 || rightVal > 0) res += max(leftVal, rightVal);
    int pathSum = node->val;
    if(leftVal > 0) pathSum += leftVal;
    if(rightVal > 0) pathSum += rightVal;
    ans = max(ans, pathSum);
    return res;
  }
  int maxPathSum(TreeNode* root) {
    ans = INT_MIN;
    dfs(root);
    return ans;
  }
};

/**
 * 酷酷的闭包写法
 */
class Solution {
public: 
  int maxPathSum(TreeNode* root) {
    int ans = INT_MIN;
    auto dfs = [&](this auto&& dfs, TreeNode* node) {
      if(node == nullptr) return 0;
      int leftVal = dfs(node->left);
      int rightVal = dfs(node->right);
      int res = node->val;
      if(leftVal > 0 || rightVal > 0) res += max(leftVal, rightVal);
      int pathSum = node->val;
      if(leftVal > 0) pathSum += leftVal;
      if(rightVal > 0) pathSum += rightVal;
      ans = max(ans, pathSum);
      return res;
    };
    dfs(root);
    return ans;
  }
};

int main() {
  // [9,6,-3,null,null,-6,2,null,null,2,null,-6,-6,-6]
  TreeNode* root = new TreeNode(9);
  root->left = new TreeNode(6);
  root->right = new TreeNode(-3);
  root->right->left = new TreeNode(-6);
  root->right->right = new TreeNode(2);
  root->right->right->left = new TreeNode(2);
  root->right->right->left->left = new TreeNode(-6);
  root->right->right->left->right = new TreeNode(-6);
  root->right->right->left->left->left = new TreeNode(-6);

  Solution solu;
  cout << solu.maxPathSum(root) << endl;
}
