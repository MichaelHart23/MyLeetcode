#include <vector>
#include <string>

using namespace std;


/*
 * 对于这个遍历，以每个元素作为左边界遍历，但每个窗口有重合的地方，每次更新窗口，要保留重合部分的信息
 */
class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    if(s.size() < p.size()) return {};
    vector<int> cnt_p, cnt_s;
    cnt_p.assign(26, 0);
    cnt_s.assign(26, 0);
    size_t size_p = p.size(), size_s = s.size();
    for(size_t i = 0; i < size_p; i++) {
      cnt_p[p[i] - 'a']++;
      cnt_s[s[i] - 'a']++;
    }
    vector<int> ans;
    for(size_t left = 0; left < size_s - size_p; left++) {
      if(cnt_p == cnt_s) ans.push_back(left);
      size_t right = left + size_p;
      cnt_s[s[left] - 'a']--;
      cnt_s[s[right] - 'a']++;
    }
    if(cnt_p == cnt_s) ans.push_back(size_s - size_p);
    return ans;
  }
};

/*
 * 我直觉上的想法，是从左向右遍历，把每个元素当作窗口的左边界来遍历
 * 但0x3f对滑动窗口的处理，是从左向右遍历，把每个元素当作窗口的右边界 
 *
 */

#ifdef RIGHT
class Solution {
public:
  vector<int> findAnagrams(string s, string p) {

  }
};
#endif

int main() {
  string s = "cbaebabacd";
  string p = "abc";
  Solution so;
  so.findAnagrams(s, p);
}