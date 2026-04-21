

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  struct DoubleNode {
    ListNode* left;
    ListNode* right;
    DoubleNode(ListNode* l, ListNode* r): left(l), right(r) {}
  };
  // 反转n个节点, 返回第 n 和第 n + 1 个节点
  DoubleNode reverseList(ListNode* head, int num) {
    ListNode *cur = head, *pre = nullptr, *temp;
    while(cur != nullptr && num > 0) {
      temp = cur->next; // 暂存后继节点 cur.next
      cur->next = pre;           // 修改 next 引用指向
      pre = cur;                // pre 暂存 cur
      cur = temp;                 // cur 访问下一节点

      num--;
    }
    return DoubleNode(pre, cur);
  }


  bool isPalindrome(ListNode* head) {
    int listSize = 0;
    ListNode* p = head;
    while(p) {
      listSize++;
      p = p->next;
    }
    DoubleNode dn = reverseList(head, listSize / 2);
    ListNode* leftHead = dn.left, *rightHead = dn.right;
    if(listSize % 2 != 0) rightHead = rightHead->next;
    while(leftHead && rightHead) {
      if(leftHead->val != rightHead->val)
        return false;
      leftHead = leftHead->next;
      rightHead = rightHead->next;
    }
    return true;
  }
};

/**
 * 0x3f的做法，很巧妙
 * 对于找中间节点，采用步长为2和步长为1的快慢指针做法，直接定位到中间节点
 * 对于反转链表，不反转前半部分，反转后半部分，这样链表甚至不会断
 */
class Solution2 {
  // 876. 链表的中间结点
  // 画图分析对于奇偶数个节点的链表，快慢指针的走法, 以及分别返回那个节点
  ListNode* middleNode(ListNode* head) {
      ListNode* slow = head, *fast = head;
      while (fast && fast->next) {
          slow = slow->next;
          fast = fast->next->next;
      }
      return slow;
  }

  // 206. 反转链表
  ListNode* reverseList(ListNode* head) {
    ListNode* pre = nullptr, *cur = head;
    while (cur) {
      ListNode* nxt = cur->next;
      cur->next = pre;
      pre = cur;
      cur = nxt;
    }
    return pre;
  }

public:
  bool isPalindrome(ListNode* head) {
      ListNode* mid = middleNode(head);
      ListNode* head2 = reverseList(mid);
      while (head2) {
          if (head->val != head2->val) { // 不是回文链表
              return false;
          }
          head = head->next;
          head2 = head2->next;
      }
      return true;
  }
};