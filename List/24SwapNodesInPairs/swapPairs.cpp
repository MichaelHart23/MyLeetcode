
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    if(head == nullptr) return nullptr;
    ListNode dummyHead = ListNode(0, head);
    ListNode* left = &dummyHead, *first = head, *second = head->next;
    while(first && second) {
      left->next = second;
      first->next = second->next;
      second->next = first;

      if(first->next == nullptr) break;
      left = first;
      first = first->next;
      second = first->next;
    }

    return dummyHead.next;
  }
};