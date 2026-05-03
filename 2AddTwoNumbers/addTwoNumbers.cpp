

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {
    }
    ListNode(int x) : val(x), next(nullptr) {
    }
    ListNode(int x, ListNode* next) : val(x), next(next) {
    }
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode dummyHead = ListNode(0);
        ListNode* cur = &dummyHead;
        while (l1 && l2) {
            int val = l1->val + l2->val + carry;
            cur->next = new ListNode(val % 10);
            carry = val / 10;
            cur = cur->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1) {
            int val = l1->val + carry;
            cur->next = new ListNode(val % 10);
            carry = val / 10;
            cur = cur->next;
            l1 = l1->next;
        }
        while (l2) {
            int val = l2->val + carry;
            cur->next = new ListNode(val % 10);
            carry = val / 10;
            cur = cur->next;
            l2 = l2->next;
        }
        if (carry != 0) cur->next = new ListNode(carry);
        return dummyHead.next;
    }
};