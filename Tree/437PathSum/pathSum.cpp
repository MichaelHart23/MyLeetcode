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
 * 一种思路：搞一个递归结构，该递归能遍历所有以node为父节点路径和（path sum）
 * 再以每个节点作为根节点调用一次，类似于一个二重循环的二重递归
 * 只是时间复杂度太高了
 */
class Solution {
public:
  int count = 0;
  void dfs(TreeNode* node, long sum, int targetSum) {
    if(node == nullptr) return;
    sum += node->val;
    if(sum == targetSum) count++;
    dfs(node->left, sum, targetSum);
    dfs(node->right, sum, targetSum);
  }
  int pathSum(TreeNode* root, int targetSum) {
    if(root == nullptr) return 0;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty()) {
      TreeNode* node = que.front();
      que.pop();
      if(node->left) que.push(node->left);
      if(node->right) que.push(node->right);
      dfs(node, 0, targetSum);
    }
    return count;
  }
};

/**
 * 可以用前缀和的思路来优化，一次遍历得到结果
 */
class Solution {
public:
  int pathSum(TreeNode* root, int targetSum) {
    unordered_map<long, int> cnt;
    int ans = 0;
    cnt[0] = 1;

    //sum代表
    auto dfs = [&](this auto&& dfs, TreeNode* node, long sum) {
      if(node == nullptr) return;
      sum += node->val;

      if(cnt.contains(sum - targetSum)) ans += cnt[sum - targetSum];

      cnt[sum]++;
      dfs(node->left, sum);
      dfs(node->right, sum);
      cnt[sum]--; //恢复现场，每到一个节点，哈希表里存的只有该节点的父节点们的前缀和
    };
    dfs(root, 0);
    return ans;
  }
};

