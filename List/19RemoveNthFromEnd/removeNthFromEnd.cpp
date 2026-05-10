
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummyHead = ListNode(0, head);
        ListNode *left = &dummyHead, *right = &dummyHead;
        while (n--) {
            right = right->next;
        }
        while (right->next) {
            right = right->next;
            left = left->next;
        }
        ListNode* del = left->next;
        left->next = del->next;
        delete del;
        return dummyHead.next;
    }
};

// 没有考虑删除头节点的情况
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* front = head, *back = head;
        while(n > 0 && front != nullptr) {
            n--;
            front = front->next;
        }
        while(front->next != nullptr) {
            front = front->next;
            back = back->next;
        }
        back->next = back->next->next;
        return head;

    }
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummyHead(0, head);
        ListNode* front = &dummyHead, *back = &dummyHead;
        while(n > 0 && front != nullptr) {
            n--;
            front = front->next;
        }
        while(front->next != nullptr) {
            front = front->next;
            back = back->next;
        }
        back->next = back->next->next;
        return dummyHead.next;

    }
};
