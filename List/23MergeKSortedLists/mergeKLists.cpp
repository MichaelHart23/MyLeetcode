#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    class MinHeap {
    public:
        vector<ListNode*> minHeap;
        void swap(int i, int j) {
            ListNode* temp = minHeap[i];
            minHeap[i] = minHeap[j];
            minHeap[j] = temp;
        }

        int left(int i) { return 2 * i + 1; }
        int right(int i) { return 2 * i + 2; }
        int parent(int i) { return (i - 1) / 2; }

    public:
        MinHeap(int n) {
            minHeap.reserve(n);
            // minHeap.resize(n);
        }
        void push(ListNode* node) {
            minHeap.push_back(node);
            int i = minHeap.size() - 1;
            while (i > 0 && minHeap[i]->val < minHeap[parent(i)]->val) {
                swap(i, parent(i));
                i = parent(i);
            }
        }

        ListNode* pop() {
            int n = minHeap.size() - 1;
            ListNode* res = minHeap[0];
            swap(0, n);
            minHeap.pop_back();
            int i = 0;
            while (true) {
                int l = left(i), r = right(i), index = i;
                if (l < n && minHeap[i]->val > minHeap[l]->val) index = l;
                if (r < n && minHeap[index]->val > minHeap[r]->val) index = r;
                if (index == i) break;
                swap(i, index);
                i = index;
            }
            return res;
        }

        ListNode* peek() { return minHeap[0]; }

        bool empty() { return minHeap.size() == 0; }
    };

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](const ListNode* a, const ListNode* b) {
            return a->val > b->val;  // 最小堆
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq;

        MinHeap minHeap(lists.size());
        for (ListNode* node : lists) {
            if (node) { minHeap.push(node); }
        }
        ListNode dummyHead = ListNode(0);
        ListNode* cur = &dummyHead;
        while (!minHeap.empty()) {
            ListNode* node = minHeap.pop();
            cur->next = node;
            cur = cur->next;
            if (node->next) { minHeap.push(node->next); }
        }
        return dummyHead.next;
    }
};

void printList(ListNode* curr) {
    while (curr != nullptr) {
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << endl;
}

void printHeap(Solution::MinHeap& minHeap) {
    for (ListNode* node : minHeap.minHeap) { cout << node->val << " "; }
    cout << endl;
}

ListNode* createList(const vector<int>& v) {
    ListNode dummyHead = ListNode();
    ListNode* cur = &dummyHead;
    for (int i : v) {
        cur->next = new ListNode(i);
        cur = cur->next;
    }
    return dummyHead.next;
}

int main() {
    // Example usage
    vector<int> v1 = {1, 4, 5};
    vector<int> v2 = {1, 3, 4};
    vector<int> v3 = {2, 6};

    ListNode* l1 = createList(v1);
    ListNode* l2 = createList(v2);
    ListNode* l3 = createList(v3);

    vector<ListNode*> lists = {l1, l2, l3};

    Solution solution;
    ListNode* merged = solution.mergeKLists(lists);

    printList(merged);

    return 0;
}
