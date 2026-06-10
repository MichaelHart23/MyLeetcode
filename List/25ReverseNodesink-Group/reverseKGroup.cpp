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

/**
 * 一段一段的反转，双开区间反转，所以在反转函数内就能保证前后连接的正确性
 */
class Solution {
public:
    void reverse(ListNode* left_end, ListNode* right_end) {
        ListNode *new_head = nullptr, *new_end = left_end->next;
        ListNode *pre = nullptr, *cur = left_end->next, *temp;
        while (cur != right_end) {
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
        if (k == 1) return head;
        int num = k;
        ListNode dummyHead = ListNode(0, head);
        ListNode *cur = head, *left_end = &dummyHead, *pre = nullptr;
        while (cur) {
            cur = cur->next;
            k--;
            if (k == 0) {
                pre = left_end->next;
                reverse(left_end, cur);
                left_end = pre;
                k = num;
                continue;
            }
        }
        return dummyHead.next;
    }
};

/**
 * 20260609，依旧是一段一段的反转，反转的函数是左闭右开的，要保证反转之后的正确性就需要额外一些操作：
 * 维护一个pre变量
 */
class Solution {
    pair<ListNode*, ListNode*> reverseAList(ListNode* head, ListNode* end) {
        ListNode dummyHead(0, head);
        ListNode* cur = head;
        ListNode* pre = &dummyHead;
        while (cur != end) {
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        dummyHead.next->next = end;
        return {pre, dummyHead.next};
    }
    void printList(ListNode* head) {
        while (head) {
            cout << head->val << " ";
            head = head->next;
        }
        cout << endl;
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) return head;
        int num = 0;
        ListNode dummyHead(0, head);
        ListNode* cur_pre = &dummyHead;
        ListNode* cur_head = head;
        ListNode* cur_end = cur_head;
        while (true) {
            while (num < k && cur_end) {
                cur_end = cur_end->next;
                num++;
            }
            if (num < k) {
                break;
            }
            auto [new_head, new_tail] = reverseAList(cur_head, cur_end);
            cur_pre->next = new_head;
            cur_pre = new_tail;
            cur_head = cur_end;
            num = 0;
        }
        return dummyHead.next;
    }
};
