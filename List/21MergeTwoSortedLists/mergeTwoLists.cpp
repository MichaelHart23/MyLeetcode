

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode dummyHead(0);
    ListNode* cur = &dummyHead;
    while(list1 && list2) {
      if(list1->val >= list2->val) {
        cur->next = list2;
        cur = cur->next;
        list2 = list2->next;
      } else {
        cur->next = list1;
        cur = cur->next;
        list1 = list1->next;
      }
    }
    // 这一行代码代替下面的两个循环，直接把剩余的尾部整体拼接过来就好，不用一个一个拼
    cur->next = list1 == nullptr? list2 : list1;
    // if(list1 != nullptr) {
    //   while(list1) {
    //     cur->next = list1;
    //     cur = cur->next;
    //     list1 = list1->next;
    //   }
    // }
    // if(list2 != nullptr) {
    //   while(list2) {
    //     cur->next = list2;
    //     cur = cur->next;
    //     list2 = list2->next;
    //   }
    // }
    return dummyHead.next;
  }
};