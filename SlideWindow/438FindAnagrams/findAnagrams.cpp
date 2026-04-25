#include <string>
#include <vector>

using namespace std;

/*
 * 对于这个遍历，以每个元素作为左边界遍历，但每个窗口有重合的地方，每次更新窗口，要保留重合部分的信息
 */
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) return {};
        vector<int> cnt_p, cnt_s;
        cnt_p.assign(26, 0);
        cnt_s.assign(26, 0);
        size_t size_p = p.size(), size_s = s.size();
        for (size_t i = 0; i < size_p; i++) {
            cnt_p[p[i] - 'a']++;
            cnt_s[s[i] - 'a']++;
        }
        vector<int> ans;
        for (size_t left = 0; left < size_s - size_p; left++) {
            if (cnt_p == cnt_s) ans.push_back(left);
            size_t right = left + size_p;
            cnt_s[s[left] - 'a']--;
            cnt_s[s[right] - 'a']++;
        }
        if (cnt_p == cnt_s) ans.push_back(size_s - size_p);
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
    vector<int> findAnagrams(string s, string p) {}
};
#endif

/**
 * 20260425重做，对于Anagrams问题，思路就是每个字符的计数作为哈希值
 * 或者排序做哈希值也行，不过那样时间复杂度是O(log n)l
 * 和49题一样
 */
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int pSize = p.size(), sSize = s.size();
        vector<int> ans;
        if(pSize > sSize) return ans;
        string ph(26, '0'), sh(26, '0');
        for(char c : p) {
            ph[c - 'a']++;
        }
        for(int i = 0; i < pSize - 1; i++) {
            sh[s[i] - 'a']++;
        }
        for(int i = 0; i < sSize - pSize + 1; i++) {
            sh[s[i + pSize - 1] - 'a']++;
            if(sh == ph) {
                ans.push_back(i);
            }
            sh[s[i] - 'a']--;
        }
        return ans;
    }
};

int main() {
    string s = "cbaebabacd";
    string p = "abc";
    Solution so;
    so.findAnagrams(s, p);
}