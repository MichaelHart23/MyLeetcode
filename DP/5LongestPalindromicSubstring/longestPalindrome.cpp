#include <bits/stdc++.h>

using namespace std;

/**
 * 中心扩散法
 */
class Solution1 {
public:
    string longestPalindrome(string s) {
        int size = s.size();
        int num = size * 2 - 1;
        pair<int, int> res = {-1, 0}; //最长子串开始的下标和其长度
        for(int i = 0; i < size; i++) { //以每个元素作为回文中心, 即所有可能的奇回文串
            int len = 1, l = i - 1, r = i + 1;
            while(l >= 0 && r < size) {
                if(s[l] == s[r]) {
                    l--;
                    r++;
                    len += 2;
                } else {
                    break;
                }
            }
            if(len > res.second) {
                res.first = l + 1;
                res.second = len;
            }
        }
        for(int i = 0; i < size - 1; i++) { //以每个空隙作为回文中心，即所有可能的偶回文串
            int l = i, r = i + 1, len = 0;
            while(l >= 0 && r < size) {
                if(s[l] == s[r]) {
                    l--;
                    r++;
                    len += 2;
                } else {
                    break;
                }
            }
            if(len > res.second) {
                res.first = l + 1;
                res.second = len;
            }
        }
        return s.substr(res.first, res.second);
    }
};

/**
 * Manacher 算法
 * 利用回文串的对称性消除了一些比较情况，但没消除很多，真的是O(n)吗？确实是
 * 
 * 在一个回文串中，有关于对称中心对称的两个元素a1和a2，
 * 右边的a2的回文半径在回文串内和a1是相等的，p[a2] = min(p[a1], right - a2)
 * 1 若a1的回文半径也在回文串内，那a1，a2的回文半径是相等的，且a2的回文半径也限死在回文串内了，不可能向外拓展了
 * 2 若a1的回文半径到达或超出的回文串的边界，那么a2的回文半径至少也能抵达回文串的边界，同时还具有向外扩展的可能
 * 根据以上，情况1直接得到了a2的回文半径；情况2时，得到a2的回文半径的一个基础值, 再根据这个基础值去扩展
 * 
 * 在一个回文串内的优化解决了，那总不能固定在一个回文串内吧，当找到一个新的回文串超出了原回文串的右边界时，
 * 就该以这个新的回文串为基准回文串了.
 * 为什么呢？因为再后面出现的串，在这个更靠右的新回文串里，有了更多的扩展可能
 * 
 * 直接手撸！NB！
 */
class Solution {
public:
    string longestPalindrome(string s) {
        int size = s.size();
        int len = 2 * size + 1;
        string t(len, '#');
        for(int i = 0; i < size; i++) {
            t[i * 2 + 1] = s[i];
        }
        vector<int> p(len, 1); //记录每个元素回文半径的数组，半径至少为1；#a#的半径是2
        int center = 0, right = 0; //当前最右回文中心和右边界
        for(int i = 0; i < len; i++) {
            if(i < right) {
                p[i] = min(p[2 * center - i], right - i + 1);
            }
            if(i + p[i] - 1 < right) continue; //情况1，不必拓展了
            //情况2，还有拓展的可能
            while(i - p[i] >= 0 && i + p[i] < len && t[i - p[i]] == t[i + p[i]]) { 
                p[i]++;
            }
            //当出现突破原回文串的边界的新回文串，更新回文串
            if(i + p[i] - 1 > right) {
                center = i;
                right = i + p[i] - 1;
            }
        }
        int start = 0, length = 0;
        for(int i = 0; i < len; i++) {
            int l = 0, r = 0;
            //根据t中索引，推导出原数组索引
            l = ((i - p[i] + 1 + 1) - 1) / 2; //原数组索引
            r = ((i + p[i] - 1 - 1) - 1) / 2; //原数组索引
            if (r - l + 1 > length) {
                start = l;
                length = r - l + 1;
            }
        }
        return s.substr(start, length);
    }
};

int main() {
    string s = "babad";
    Solution so;
    cout << so.longestPalindrome(s);
}

