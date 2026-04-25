#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> set_;
        int res = 0, left = 0;
        size_t size = s.size();

        for (int i = 0; i < size; i++) {
            while (set_.find(s[i]) != set_.end()) {
                set_.erase(s[left]);
                left++;
            }
            res = max(res, i - left + 1);
            set_.insert(s[i]);
        }
        return res;
    }
};

/**
 * 20260425重做
 * 和128的思路有点像，都是用哈希表把查找复杂度降到O(1)
 */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int size = s.size();
        unordered_set<char> us;
        int left = 0, right = 0, ans = 0;
        while(right < size) {
            auto it = us.find(s[right]);
            if(it == us.end()) {
                us.insert(s[right]);
                right++;
                ans = max(ans, right - left);
            } else {
                us.erase(s[left]);
                left++;
            }
        }
        return ans;
    }
};

int main() { std::cout << sizeof(size_t) << std::endl; }