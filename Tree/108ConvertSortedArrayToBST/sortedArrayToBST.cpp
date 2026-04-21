#include <vector>
#include <iostream>

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
  TreeNode* binarySearchContrust(int left, int right, vector<int>& nums) {
    if(left > right) return nullptr;
    if(left == right) {
      return new TreeNode(nums[left]);
    }
    int mid = (left + right) / 2;
    TreeNode* node = new TreeNode(nums[mid]);
    node->left = binarySearchContrust(left, mid - 1, nums);
    node->right = binarySearchContrust(mid + 1, right, nums);
    return node;
  }
  TreeNode* sortedArrayToBST(vector<int>& nums) {
    return binarySearchContrust(0, nums.size() - 1, nums);
  }
};

void preOrder(TreeNode* node) {
  if(node == nullptr) return;
  cout << node->val << " ";
  preOrder(node->left);
  preOrder(node->right);
}
int main() {
  vector<int> nums = {-10, -3, 0, 5, 9};
  Solution s;
  TreeNode* root = s.sortedArrayToBST(nums);
  preOrder(root);
}