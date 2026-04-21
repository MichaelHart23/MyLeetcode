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

class Solution {
public:
  vector<vector<int>> levelOrder(TreeNode* root) {
    if(root == nullptr) return {};
    vector<vector<int>> res;
    vector<TreeNode*> que;
    que.push_back(root);
    while(!que.empty()) {
      vector<TreeNode*> newQueue;
      vector<int> nodes;
      for(auto it : que) {
        nodes.push_back(it->val);
        if(it->left) newQueue.push_back(it->left);
        if(it->right) newQueue.push_back(it->right);
      }
      res.push_back(move(nodes));
      que = move(newQueue);
    }
    return res;
  }
};
