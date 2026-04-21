#include <vector>

using namespace std;

class Solution {
public:
  void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
  }

  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    for(int i = 0; i < n / 2; i++) {
      swap(nums[i], nums[n - 1 - i]);
    }
    for(int i = 0; i < k / 2; i++) {
      swap(nums[i], nums[k - 1 - i]);
    }
    for(int i = k; i < k + (n - k) / 2; i++) {
      swap(nums[i], nums[k + n - 1 - i]);
    }
  }

  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    auto reverse = [&](int i, int j) {
      while(i < j) {
        swap(nums[i++], nums[j++]);
      }
    };
    reverse(0, n - 1);
    reverse(0, k - 1);
    reverse(k, n - 1);
  }
};