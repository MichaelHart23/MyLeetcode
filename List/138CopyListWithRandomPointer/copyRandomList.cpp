#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
// Definition for a Node.
class Node {
public:
  int val;
  Node* next;
  Node* random;
  
  Node(int _val) {
    val = _val;
    next = NULL;
    random = NULL;
  }
};


class Solution {
public:
  Node* copyRandomList(Node* head) {
    vector<int> index; // 表示第i个节点的random指向第几个节点
    vector<Node*> v; // 表示第i个节点存储的random指针
    unordered_map<Node*, int> m1; //表示原链表中某node对应链表中下标
    unordered_map<int, Node*> m2; //表示新链表中下标对应的节点
    Node dummyHead = Node(0);
    Node* cur = &dummyHead, *it = head;
    int n = 0;
    while(it) {
      cur->next = new Node(it->val);
      v.push_back(it->random);
      m1[it] = n;
      m2[n] = cur->next;

      n++;
      cur = cur->next;
      it = it->next;
    }
    for(int i = 0; i < n; i++) {
      if(v[i] == nullptr) {
        index.push_back(-1);
      } else {
        index.push_back(m1[v[i]]);
      }
    }
    cur = dummyHead.next, n = 0;
    while(cur) {
      if(index[n] == -1) {
        cur->random = nullptr;
      } else {
        cur->random = m2[index[n]];
      }
      cur = cur->next;
      n++;
    }
    return dummyHead.next;
  }
};