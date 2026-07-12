#include <bits/stdc++.h>

using namespace std;

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
    void reverse(ListNode* leftEnd, ListNode* rightEnd, ListNode* start) {
        ListNode dummyHead(0, start);
        ListNode *pre = &dummyHead, *cur = start;
        while (cur != rightEnd) {
            auto temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        start->next = rightEnd;
        leftEnd->next = pre;
    }
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode dummyHead(0, head);
        ListNode* pre = &dummyHead, *cur = head;
        int i = 1;
        ListNode *leftEnd, *rightEnd, *start;
        while (cur) {
            if (i == left) {
                leftEnd = pre;
                start = cur;
            }
            if (i == right) {
                rightEnd = cur->next;
                break;
            }
            pre = cur;
            cur = cur->next;
            i++;
        }
        reverse(leftEnd, rightEnd, start);
        return dummyHead.next;
    }
};
