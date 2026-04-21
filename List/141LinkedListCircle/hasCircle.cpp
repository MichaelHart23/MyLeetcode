

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * 步长为1和步长为2的快慢指针，若有环一定相遇
 */
class Solution {
public:
  bool hasCycle(ListNode *head) {
    ListNode* fast = head, *slow = head;
    while(fast && fast->next) {
      fast = fast->next->next;
      slow = slow->next;
      if(fast == slow) return true;
    }
    return false;
  }
};