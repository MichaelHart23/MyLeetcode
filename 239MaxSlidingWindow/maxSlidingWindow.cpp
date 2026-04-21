#include <vector>
#include <set>
#include <deque>
using namespace std;

#define DEQUE

/*
 * 解决改题目根本在于如何用更少的时间复杂度去找到窗口内的最大值
 * set本身就是排好序的，找到最大值的时间复杂度是log k
 * 但set是不允许重复的，所以改用multimap
 */


#ifdef SET
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    if(k == 1)
      return nums;
    int n = nums.size();
    vector<int> res;
    res.reserve(n - k + 1);
    multiset<int> s;
    for(int i = 0; i < k; i++) 
      s.insert(nums[i]);
    for(int left = 0, right = k; ; left++, right++) {
      res.push_back(*s.rbegin());
      if(right >= n)
        break;
      s.erase(s.find(nums[left]));
      s.insert(nums[right]);
    }
    return res;
  }
};
#endif

/*
 * 用单调队列去找到窗口内的最大值，时间复杂度是O(1)
 * 当出窗口的元素就是窗口内的最大值时，也能保证第二大的元素仍然保留，而不用重新找出最大的元素
 */
#ifdef DEQUE
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    if(k == 1)
      return nums;
    deque<int> d;
    vector<int> res;
    int n = nums.size();
    res.reserve(n - k + 1);
    for(int i = 0; i < k; i++) { //填充好第一个窗口
      /* 把小于nums[i]的元素全部pop，再把该元素push,
       * 以此维护队列的单调性 */
      while(!d.empty() && d.back() < nums[i])
        d.pop_back();
      d.push_back(nums[i]);
    }
    for(int left = 0, right = k; ;left++, right++) {
      res.push_back(d.front());
      if(right >= n) //当right是n时，就是最后一个窗口了，就表明最后一个窗口的max也加入res了
        break;
      // 当需要把窗口最左端的数pop的时候，当它不是队列中的最大值的时候，即使不pop，也不会出问题。因为
      if(d.front() == nums[left])
        d.pop_front();
      while(!d.empty() && d.back() < nums[right])
        d.pop_back();
      d.push_back(nums[right]);
    }
    return res;
  }
};
#endif
