
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
  void reverse(ListNode* left_end, ListNode* right_end) {
    ListNode* new_head = nullptr, *new_end = left_end->next;
    ListNode* pre = nullptr, *cur = left_end->next, *temp;
    while(cur != right_end) {
      temp = cur->next;
      cur->next = pre;
      pre = cur;
      cur = temp;
    }
    new_head = pre;
    left_end->next = new_head;
    new_end->next = right_end;
  }
  ListNode* reverseKGroup(ListNode* head, int k) {
    if(k == 1) return head;
    int num = k;
    ListNode dummyHead = ListNode(0, head);
    ListNode* cur = head, *left_end = &dummyHead, *pre = nullptr;
    while(cur) {
      cur = cur->next;
      k--;
      if(k == 0) {
        pre = left_end->next;
        reverse(left_end ,cur);
        left_end = pre;
        k = num;
        continue;
      }
    }
    return dummyHead.next;
  }
};