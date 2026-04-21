#include <stack>   // std::stack
#include <utility> // std::pair, std::make_pair
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printList(ListNode* curr) {
  while (curr != nullptr) {
    cout << curr->val << " ";
    curr = curr->next;
  }
  cout << endl;
}

ListNode* createList(const vector<int>& v) {
  ListNode dummyHead = ListNode();
  ListNode* cur = &dummyHead;
  for(int i : v) {
    cur->next = new ListNode(i);
    cur = cur->next;
  }
  return dummyHead.next;
}

class Solution {
  ListNode* middle_node(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode dummyHead = ListNode(0, head);
    ListNode* slow = &dummyHead, *fast = &dummyHead;
    while(fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    } 
    return slow;
  }

  ListNode* merge_sorted_list(ListNode* list1, ListNode* list2) {
    ListNode dummyHead = ListNode();
    ListNode* cur = &dummyHead;
    while(list1 && list2) {
      if(list1->val > list2->val) {
        cur->next = list2;
        list2 = list2->next;
      } else {
        cur->next = list1;
        list1 = list1->next;
      }
      cur = cur->next;
    }
    cur->next = list1 == nullptr? list2 : list1;
    return dummyHead.next;
  }
public:
  ListNode* sortList(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return head;
    ListNode* middle = middle_node(head);
    ListNode* middle_next = middle->next;
    middle->next = nullptr;

    ListNode* n1 = sortList(head);
    ListNode* n2 = sortList(middle_next);
    return merge_sorted_list(n1, n2);
  }
};

/**
 * 迭代实现链表的归并排序
 * 初步思路：
 * 两个栈
 * 一个模仿递归调用的过程不断二分
 * 一个存储以及排序好的链表的头节点
 * 行不通
 * 
 * 先一个一个聚合成两个，再两个两个聚合成四个，以此类推
 * 在每次找两个单元并聚合的时候
 * 1 需要找到固定个数的节点
 * 2 需要把合并完的节点们添加到新链表的末尾
 * 3 要能开始新一轮的二二合并
 * 
 * 所以要维护一个指向新链表结尾的指针，还有一个指向旧链表下一个需要被被合并的节点的指针
 */
class Solution2 {
  /**
   * 找长为size的子链表，若能找到，返回下一个节点，若找不到，返回nullptr
   */
  ListNode* findSizeList(ListNode* head, int size) {
    if(size <= 0) return head; //在被调用时只会传入1，2，4…… 这样的数，不过以防万一 
    int n = 0;
    while(head) {
      n++;
      if(n >= size) break;
      head = head->next;
    }
    if(head == nullptr) {
      return nullptr;
    }
    ListNode* res = head->next;
    head->next = nullptr;
    return res;
  }

  /**
   * 合并有序链表，并返回新链表的头和尾
   */
  std::pair<ListNode*, ListNode*> mergeSortedList(ListNode* list1, ListNode* list2) {
    ListNode dummyHead = ListNode();
    ListNode* cur = &dummyHead;
    while(list1 && list2) {
      if(list1->val > list2->val) {
        cur->next = list2;
        list2 = list2->next;
      } else {
        cur->next = list1;
        list1 = list1->next;
      }
      cur = cur->next;
    }
    cur->next = list1 == nullptr? list2 : list1;
    while(cur->next) {
      cur = cur->next;
    }
    return std::make_pair(dummyHead.next, cur);
  }

  public:
  ListNode* sortList(ListNode* head) { 
    if(head == nullptr || head->next == nullptr) return head;
    ListNode dummyHead = ListNode(0, head); //用来承接新链表
    int step = 1;
    ListNode* cur = head, *newListTail = &dummyHead;

    while(true) {
      int couples = 0; //合并了多少对，当仅合并一对的时候，就是结束循环的时候
      cur = dummyHead.next;
      newListTail = &dummyHead;
      while(cur) {
        ListNode* head1 = cur;
        ListNode* head2 = findSizeList(cur, step);
        ListNode* newHead = findSizeList(head2, step);

        auto [head, tail] = mergeSortedList(head1, head2);
        //auto headAndTail = mergeSortedList(head1, head2);
        newListTail->next = head;
        newListTail = tail;

        cur = newHead;
        couples++;
      }

      if(couples == 1) break;

      step *= 2;
    }
    return dummyHead.next;
  }
};


/**
 * 快排实现链表排序
 */
class SolutionQuickSort {
  /**
   * 交换两个节点的后一个节点的位置
   * 
   * 不再使用该函数了
   */
  void swap(ListNode* node1, ListNode* node2) {
    if(node1 == node2) return;  
    if(node1->next == node2) {
      node1->next = node2->next;
      node2->next = node1->next->next;
      node1->next->next = node2;
      return;
    }
    ListNode* n1Next = node1->next;
    ListNode* n1NextNext = node1->next->next;
    n1Next->next = node2->next->next;
    node2->next->next = n1NextNext;
    node1->next = node2->next;
    node2->next = n1Next;
  }

  /**
   * pre是待排序链表的前一个节点，可是是dummy；end是待排序链表的后一个节点，可能是nullptr
   * 
   * 链表特殊的地方就是其灵活性，不必执着于像数组一样交换他们的位置，可以直接构造一个新链表来承接比pivot小的节点
   */
  void quickSort(ListNode* pre, ListNode* end) {
    //没有节点和只有一个节点的情况
    if(pre->next == end || pre->next->next == end) return;
    ListNode* pivot = pre->next;
    pre->next = pre->next->next; //把pivot节点单独摘出来，方便后续插入
    ListNode dummyHead = ListNode(0); //构造一个新链表，用来承接比pivot小的节点
    ListNode* cur = pre, *nextPosition = &dummyHead;
    while(cur->next != end) {
      if(cur->next->val < pivot->val) {//从原链表中删除，插入新链表
        nextPosition->next = cur->next;
        cur->next = cur->next->next;
        nextPosition = nextPosition->next;
      } else 
        cur = cur->next;
    }
    nextPosition->next = pivot;
    pivot->next = pre->next;
    pre->next = dummyHead.next;
    quickSort(pre, pivot);
    quickSort(pivot, end);
  }
public:
  ListNode* sortList(ListNode* head) {
    ListNode dummyHead = ListNode(0, head);
    quickSort(&dummyHead, nullptr);
    return dummyHead.next;
  }
};

int main() {
  ListNode* head = createList({-1, 5, 3, 4, 0});
  // Solution2 s2;
  // s2.sortList(head);
  SolutionQuickSort sq;
  printList(sq.sortList(head));
}