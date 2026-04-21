#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
    unordered_set<int> u_set(nums.begin(),nums.end());
    int res = 0;
    for(int i : u_set) {
      if(u_set.find(i - 1) != u_set.end()) {
        continue;
      }
      int len = 1;
      while(u_set.find(i + len) != u_set.end()) {
        len++;
      }
      res = max(res, len);
    }
    return res;
  }
};