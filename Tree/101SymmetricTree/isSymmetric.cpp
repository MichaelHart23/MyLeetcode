

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
  //两个对称位置的node，他们的值是否相同，以及他们的子节点是否也对称
  bool isSame(TreeNode* left, TreeNode* right) {
    if(left == nullptr && right == nullptr) return true;
    else if(left == nullptr || right == nullptr || left->val != right->val) return false;
    return isSame(left->left, right->right) && isSame(left->right, right->left);

  }
  bool isSymmetric(TreeNode* root) {
    if(root == nullptr) return true;
    return isSame(root->left, root->right);
  }
};