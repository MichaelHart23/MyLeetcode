# 采用颜色标记法来遍历二叉树，WHITE表示第一次访问这个节点，按照遍历顺序把（左中右）入栈
# 该节点以灰GRAY入站，新节点以WHITE入栈
# GRAY表示回溯到了这个节点，需要把这个节点加入数组了
# leetcode的一位作者原创
class Solution:
  def inorderTraversal(self, root: TreeNode) -> List[int]:
    WHITE, GRAY = 0, 1
    res = []
    stack = [(WHITE, root)]
    while stack:
      color, node = stack.pop()
      if node is None: continue
      if color == WHITE:
        stack.append((WHITE, node.right))
        stack.append((GRAY, node))
        stack.append((WHITE, node.left))
      else:
        res.append(node.val)
    return res
