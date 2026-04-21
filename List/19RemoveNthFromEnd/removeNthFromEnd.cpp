
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummyHead = ListNode(0, head);
    ListNode* left = &dummyHead, *right = &dummyHead;
    while(n--) {
      right = right->next;
    }
    while(right->next) {
      right = right->next;
      left = left->next;
    }
    ListNode* del = left->next;
    left->next = del->next;
    delete del;
    return dummyHead.next;
  }
};