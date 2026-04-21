#include <string>
#include <unordered_map>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_set<char> set_;
    int res = 0, left = 0;
    size_t size = s.size();

    for(int i = 0; i < size; i++) {
      while(set_.find(s[i]) != set_.end()) {
        set_.erase(s[left]);
        left++;
      }
      res = max(res, i - left + 1);
      set_.insert(s[i]);
    }
    return res;
  }
};

int main() {
  std::cout << sizeof(size_t) << std::endl;
}