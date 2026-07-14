#include <bits/stdc++.h>

using namespace std;


/**
 * 如果用一个有序数组来表示，那么插入的复杂度是O(n)，查找是O(1)，且涉及到大量的内存重新分配，不行
 * 那怎么降低插入的实际复杂度呢？
 * 唉！二叉有序树！(二叉搜索树)但怎么保持二叉有序树的平衡呢？
 * 
 * 
 * 直接分成两堆，一个最大堆，一个最小堆
 * 最大堆里存的较小的一半元素，最小堆里存的是较大的一半元素
 * 保持左堆里的元素比右堆多一或者两堆相等
 */
class MedianFinder {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int maxSize = maxHeap.size(), minSize = minHeap.size();
        if(maxSize == 0) { //双堆皆为0
            maxHeap.push(num);
            return;
        }
        if(minSize == 0) { //左堆为1，右堆为0
            if(num >= maxHeap.top()) {
                minHeap.push(num);
            } else {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
                maxHeap.push(num);
            }
            return;
        }
        int maxTop = maxHeap.top(), minTop = minHeap.top();
        if(maxSize == minSize) {
            if(num > minTop) {
                maxHeap.push(minTop);
                minHeap.pop();
                minHeap.push(num);
            } else {
                maxHeap.push(num);
            }
        } else if(maxSize - minSize == 1) {
            if(num < maxTop) {
                minHeap.push(maxTop);
                maxHeap.pop();
                maxHeap.push(num);
            } else {
                minHeap.push(num);
            }
        }            
    }
    
    double findMedian() {
        int maxSize = maxHeap.size(), minSize = minHeap.size();
        if(maxSize == minSize) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            return maxHeap.top();
        }
    }
};

/**
 * 0x3f的简洁实现：
 */
class MedianFinder {
    priority_queue<int> left; // 最大堆
    priority_queue<int, vector<int>, greater<int>> right;
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        //要把较小的一个数加入到左堆中，可以直接用最小堆把这个数“筛”出来
        if(left.size() == right.size()) {
            right.push(num);
            left.push(right.top());
            right.pop();
        } else { //要把一个较大的数加入右堆，利用最大堆把这个数筛出来
            left.push(num);
            right.push(left.top());
            left.pop();
        }
    }
    
    double findMedian() {
        if(left.size() == right.size()) {
            return (left.top() + right.top()) / 2.0;
        }
        return left.top(); // 最大堆多1
    }
};

/**
 * 20260714  只允许两种情况，两堆的大小一样；最大堆比最小堆多1
 */
class MedianFinder {
    priority_queue<int> maxHeap; // 最大堆存较小的一半
    priority_queue<int, vector<int>, greater<int>> minHeap; // 最小堆存较大的一半
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (maxHeap.size() == 0) {
            maxHeap.push(num);
            return;
        }
        if (num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        if (maxHeap.size() > minHeap.size()) {
            while (maxHeap.size() - minHeap.size() > 1) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            }
        } else {
            while (minHeap.size() > maxHeap.size()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }
    }
    
    double findMedian() {
        if (minHeap.size() == maxHeap.size()) {
            return ((double)maxHeap.top() + minHeap.top()) / 2;
        } else {
            return maxHeap.top();
        }
    }
};

int main() {
    MedianFinder m;
    m.addNum(-1);
    m.addNum(-2);
    cout << m.findMedian();
}

