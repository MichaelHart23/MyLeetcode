#include <bits/stdc++.h>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> s;
        //为了防止单一链表过长的情况，不用这种方法
        // while(headA) { 
        //     s.insert(headA);
        //     headA = headA->next;
        // }
        // while(headB) {
        //     if(s.find(headB) != s.end()) {
        //         return headB;
        //     } else {
        //         s.insert(headB);
        //         headB = headB->next;
        //     }
        // }
        while(true) {
            if(!headA && !headB) break;
            if(headA) {
                if(s.find(headA) != s.end()) {
                    return headA;
                } else {
                    s.insert(headA);
                    headA = headA->next;
                }
            }
            if(headB) {
                if(s.find(headB) != s.end()) {
                    return headB;
                } else {
                    s.insert(headB);
                    headB = headB->next;
                }
            }
        }
        return nullptr;
    }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* a = headA, *b = headB;
        while(a != b) {
            a = a ? a->next : headB;
            b = b ? b->next : headA;
        }
        return a;
    }
};
