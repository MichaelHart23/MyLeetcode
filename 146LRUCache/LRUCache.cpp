#include <vector>
#include <iostream>

using namespace std;

/**
 * 数组版，宣告失败
 */

class LRUCache {
public:
  class Node {
  public:
    int key;
    int value;
    int prev;
    int next;
    Node() : key(0), value(0), prev(-1), next(-1) {}
    Node(int k, int v) : key(k), value(v), prev(-1), next(-1) {}
    Node(int k, int v, int n) : key(k), value(v), prev(-1), next(n) {}
  };
  
  Node dummyHead;
  int capacity;
  int size;
  Node* cache;
  int head;

  void set(int index, int key, int value) {
    cache[index].key = key;
    cache[index].value = value;
    cache[index].prev = -1;
    cache[index].next = -1;
  }
  void insert(int key, int value) {
    int cur = head;
    while(cur != -1) {
      if(cache[cur].key == key) {
        cache[cur].value = value;
        return;
      }
      cur = cache[cur].next;
    }
    cache[size].key = key;
    cache[size].value = value;
    cache[size].next = head; //新头
    head = size;
    size++;
  }
  void insert2FullCache(int key, int value) {
    int cur = head;
    int newTail;
    while(cache[cur].next != -1) {
      if(cache[cur].key == key) {
        cache[cur].value = value;
        return;
      }
      if(cache[cache[cur].next].next == -1) {
        newTail = cur;
      }
      cur = cache[cur].next;
    }
    if(cache[cur].key == key) {
      cache[cur].value = value;
    } else {
      cache[newTail].next = -1;
      cache[cur].key = key;
      cache[cur].value = value;
      cache[cur].next = head;
      head = cur;
    }
  }

  void printCache() {
    int cur = head;
    while(cur != -1) {
      cout << cache[cur].key << ":" << cache[cur].value << " ";
      cur = cache[cur].next;
    }
    cout << endl;
  }

  LRUCache(int capacity) {
    this->capacity = capacity;
    cache = new Node[capacity];
    size = 0;
    head = -1;
  }
  
  int get(int key) {
    if(size == 0) return -1;
    if(cache[head].key == key) return cache[head].value;
    int cur = head;
    int newHead = -1;
    while(cache[cur].next != -1) {
      int next = cache[cur].next;
      if(cache[next].key == key) {
        newHead = next;
        break;
      }
    }
    if(newHead != -1) {
      cache[cur].next = cache[newHead].next;
      cache[newHead].next = head;
      head = newHead;
      return cache[newHead].value;
    }
    return -1;
  }
  
  void put(int key, int value) {
    if(size == capacity) {
      insert2FullCache(key, value);
    } else if(size == 0) {
      set(0, key, value);
      head = 0;
      size++;
    } else {
      insert(key, value);
    }
  }
};

void printCache(LRUCache* cache) {
  int cur = cache->head;
  while(cur != -1) {
    cout << cache->cache[cur].key << ":" << cache->cache[cur].value << " ";
    cur = cache->cache[cur].next;
  }
  cout << endl;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
  LRUCache* obj = new LRUCache(2);
  obj->put(1, 1);
  obj->put(2, 2);
  cout << obj->get(1) << endl; // 返回 1
  obj->put(3, 3); // 该操作会使得密钥 2 作废
  cout << obj->get(2) << endl; // 返回 -1 (未找到)
  obj->put(4, 4); // 该操作会使得密钥 3 作废
  cout << obj->get(3) << endl; // 返回 -1 (未找到)
  cout << obj->get(4) << endl; // 返回 4
}