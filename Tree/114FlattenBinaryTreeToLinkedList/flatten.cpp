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


/**
 * 自底向上flat，总体就是把左子节点放在父节点和右子节点之间
 * 
 * 每个递归单元的任务是，把以node为父节点的子树转化为链表，并返回链表尾
 */
class Solution {
public:
  TreeNode* doFlat(TreeNode* node) {
    if(node == nullptr) return nullptr;
    TreeNode* leftNode = node->left;
    TreeNode* rightNode = node->right;
    TreeNode* leftTail = doFlat(leftNode);
    TreeNode* rightTail = doFlat(rightNode);
    if(leftTail != nullptr) {
      node->right = leftNode;
    } else {
      leftTail = node;
    }
    // 右尾巴是空不是空都一样
    leftTail->right = rightNode;
    node->left = nullptr;
    return rightTail == nullptr ? leftTail : rightTail;
  }
  void flatten(TreeNode* root) {
    if(root == nullptr) return;
    doFlat(root);
  }
};

/**
 * 按最终形成链表的倒序遍历该树，按照链表插入节点的方式一个个插入
 * 遍历顺序为：右子树->左子树->父节点
 * 由于是按照链表序遍历的，所以遍历到一个节点的时候只需要把这个节点加入链表就好了
 */
class Solution {
public:
  TreeNode* head = nullptr;
  void doFlat(TreeNode* node) {
    if(node == nullptr) return;
    doFlat(node->right);
    doFlat(node->left);
    //当遍历到某个节点时，该把这个节点加入到链表
    node->left = nullptr;
    node->right = head;
    head = node;
  }
  void flatten(TreeNode* root) {
    if(root == nullptr) return;
    doFlat(root);
  }
};

void printTree(TreeNode* node) {
  while(node != nullptr) {
    cout << node->val << " ";
    node = node->right;
  }
  cout << endl;
}

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(5);
  root->left->left = new TreeNode(3);
  root->left->right = new TreeNode(4);
  root->right->right = new TreeNode(6);

  Solution s;
  s.flatten(root);
  printTree(root);
}
