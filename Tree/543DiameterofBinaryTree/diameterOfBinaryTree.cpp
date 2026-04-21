#include <algorithm>

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
 * 就是找一个节点，该节点的左高度加右高度最大
 * 此处左高度是指从某个节点出发，到其左最远叶子节点所经过的边数
 * 右高度是指从某个节点出发，到其右最远叶子节点所经过的边数
 */
class Solution {
public:
  //找到节点node到其最远子节点的经过的边数
  int findDepth(TreeNode* node, int& res) {
    if(node == nullptr) {
      return 0;
    }
    int leftDepth = findDepth(node->left, res);
    int rightDepth = findDepth(node->right, res);
    res = max(res, leftDepth + rightDepth);
    return max(leftDepth + 1, rightDepth + 1);
  }
  int diameterOfBinaryTree(TreeNode* root) {
    int res = 0;
    findDepth(root, res);
    return res;
  }
};