#include <unordered_map>

using namespace std;

class LRUCache {
    class Node {
    public:
        int key;
        int value;
        Node* prev;
        Node* next;
    };

    Node dummyHead;
    int capacity;
    int size;
    unordered_map<int, Node*> map;  // key 和 node 的哈希表，加速查询

    // 把一个节点放到链表头
    void insert2Head(Node* node) {
        node->next = dummyHead.next;
        node->prev = &dummyHead;
        dummyHead.next->prev = node;
        dummyHead.next = node;
    }

    // 把双向链表中的节点移动到链表头
    void move2Head(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        insert2Head(node);
    }

    int evictTail() {  // 移除尾部节点，并返回其key
        Node* tail = dummyHead.prev;
        int key = tail->key;
        tail->prev->next = &dummyHead;
        dummyHead.prev = tail->prev;
        delete tail;
        return key;
    }

public:
    LRUCache(int _capacity) {
        capacity = _capacity;
        size = 0;
        dummyHead.prev = dummyHead.next = &dummyHead;
    }
    int get(int key) {
        if (!map.contains(key)) return -1;
        Node* node = map[key];
        move2Head(node);
        return node->value;
    }

    void put(int key, int value) {
        Node* node;
        if (map.contains(key)) {  // cache已经有了该key
            node = map[key];
            node->value = value;
            move2Head(node);
            return;
        }
        // cache中没有该key
        node = new Node(key, value);
        if (size == capacity) {
            map.erase(evictTail());  // 从尾部移除同时从哈希表中移除
            insert2Head(node);
        } else {
            insert2Head(node);
            size++;
        }
        map[key] = node;
    }
};

int main() {
    // ["LRUCache","put","put","get","put","put","get"]
    // [[2],[2,1],[2,2],[2],[1,1],[4,1],[2]]
    LRUCache* cache = new LRUCache(2);
    cache->put(2, 1);
    cache->put(2, 2);
    cache->get(2);
    cache->put(1, 1);
    cache->put(4, 1);
    cache->get(2);
}