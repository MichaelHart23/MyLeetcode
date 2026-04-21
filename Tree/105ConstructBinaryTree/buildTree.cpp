#include <vector>
#include <iostream>
#include <stack>
#include <span>
#include <ranges>
#include <unordered_map>

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
 * 递归单元的结构为：给定一棵树在两数组中的范围，构建完成这棵树，返回树根
 */
class Solution {
public:
  TreeNode* build(vector<int>& preorder, int preLeft, int preRight,
                  vector<int>& inorder, int inLeft, int inRight) {
    if(preLeft > preRight) return nullptr;
    if(preLeft == preRight) return new TreeNode(preorder[preLeft]);
    int i, leftNums, rightNums;
    int rootVal = preorder[preLeft];
    for(i = inLeft; i <= inRight; i++) {
      if(inorder[i] == rootVal) break;
    }
    leftNums = i - inLeft;
    rightNums = inRight - i;
    TreeNode* rootNode = new TreeNode(rootVal);
    rootNode->left = build(preorder, preLeft + 1, preLeft + leftNums, inorder, inLeft, inLeft + leftNums - 1);
    rootNode->right = build(preorder, preLeft + leftNums + 1, preRight, inorder, i + 1, inRight);
    return rootNode;
  }
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
  }
};

/**
 * 和上面一样的实现思路，用span简化代码
 */
class Solution {
  TreeNode* build(span<int> preorder, span<int> inorder) {
    if (preorder.empty()) { // 空节点
      return nullptr;
    }
    int left_size = ranges::find(inorder, preorder[0]) - inorder.begin(); // 左子树的大小
    TreeNode* left = build(preorder.subspan(1, left_size), inorder.subspan(0, left_size));
    TreeNode* right = build(preorder.subspan(1 + left_size), inorder.subspan(1 + left_size));
    return new TreeNode(preorder[0], left, right);
  }

public:
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return build(preorder, inorder);
  }
};

/**
 * 用哈希表记录inorder数组中各个节点的下标，这样可以优化找根节点的时间
 */
class Solution {
public:
  unordered_map<int, int> dict;
  
  TreeNode* build(vector<int>& preorder, int preLeft, int preRight,
                  vector<int>& inorder, int inLeft, int inRight) {
    if(preLeft > preRight) return nullptr;
    if(preLeft == preRight) return new TreeNode(preorder[preLeft]);
    int i, leftNums, rightNums;
    int rootVal = preorder[preLeft];
    i = dict[rootVal];
    leftNums = i - inLeft;
    rightNums = inRight - i;
    TreeNode* rootNode = new TreeNode(rootVal);
    rootNode->left = build(preorder, preLeft + 1, preLeft + leftNums, inorder, inLeft, inLeft + leftNums - 1);
    rootNode->right = build(preorder, preLeft + leftNums + 1, preRight, inorder, i + 1, inRight);
    return rootNode;
  }
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int size = preorder.size();
    for(int i = 0; i < size; i++) {
      dict[inorder[i]] = i;
    }
    return build(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
  }
};
