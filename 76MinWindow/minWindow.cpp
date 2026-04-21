#include<vector>
#include<string>
#include<unordered_set>
#include <set>

using namespace std;

/*
class Solution {
public:
  string minWindow(string s, string t) {
    int m = s.size(), n = t.size();
    if(m < n)
      return "";
    unordered_multiset<char> origin;
    for(int i = 0; i < n; i++) {
      origin.insert(t[i]);
    }
    string res;
    int first = 0, second = 0, last = 0;
    while(!origin.contains(s[first]))
      first++;
    while(true) {
      unordered_multiset<char> copy(origin);
      unordered_multiset<char>::iterator it;
      for(int i = first; i < m; i++) {
        it = copy.find(s[i]);
        if(it != copy.end()) {
          if(second == 0 && copy.size() < n) {
            second = i;
          }
          copy.erase(it);
        }
        if(copy.empty()) {
          last = i;
          break;
        }
      }
      if(!copy.empty())
        break;
      if(res.size() > last - first + 1) {
        res = s.substr(first, last - first + 1);
      }
      first = second;
    }


    return res;
    
    
      
  }
};


class Solution2 {
public:
  string minWindow(string s, string t) {
    int m = s.size(), n = t.size();
    if(m < n || n == 0)
      return "";
    unordered_multiset<char> origin;
    for(int i = 0; i < n; i++) {
      origin.insert(t[i]);
    }
    string res;
    int first = 0, last = 0;
    while(!origin.contains(s[first])) //找到第一个t的字符
      first++;
    int second = first;
    unordered_multiset<char>::iterator it;
    for(int i = first; i < m; i++) {
      it = origin.find(s[i]);
      if(it != origin.end()) {
          if(second == first && origin.size() < n) {
            second = i;
          }
          origin.erase(it);   
      }
      if(origin.empty()) {
          last = i;
          break;
      }
    }
    res = s.substr(first, last - first + 1);
    while(true) {
      unordered_multiset<char> origin;
      for(int i = first + 1; i < m; i++) {
        it = origin.find(s[i]);
        if(it != origin.end()) {
          if(second <= first) {
            second = i;
          }
          origin.erase(it);   
        }
        if(origin.empty()) {
          last = i;
          break;
        }
      }
      if(!origin.empty())
        break;
      if(res.size() > last - first + 1) {
        res = s.substr(first, last - first + 1);
      }
      origin.insert(s[first]);
      first = last;
    }


    return res;
    
    
      
  }
};
*/

/* 整体思路是一个滑动窗口，每当窗口拓展至可以囊括t时，即得到一个符合条件的子串时，和此前的子串对比长度，选择
 * 长度较小的子串。
 * 之后把窗口内的第一个字符去除，从第二个字符作为新的窗口左边界，从此时的窗口右边界开始，找到新的符合条件的窗
 * 口。
 */
class Solution3 {
public:
  string minWindow(string s, string t) {
    int m = s.size(), n = t.size();
    string res = "";
    if(m < n || n == 0)
      return res;
    unordered_multiset<char> origin; //存储t字符串
    for(int i = 0; i < n; i++) {
      origin.insert(t[i]);
    }
    set<int> index_set;   //存储s字符串中匹配t字符串的字符的index，即窗口和窗口中对t字符的标记
    unordered_multiset<char>::iterator it;
    for(int i = 0; i < m; i++) {
      it = origin.find(s[i]);
      if(it != origin.end()) { //每当在s中找到一个在t中的字符，把索引放到index_set，把字符从origin中删去
        index_set.insert(i);
        origin.erase(it);
      }
      if(origin.empty()) { //找到一个符合条件的子串
        int first = *index_set.begin(), last = *index_set.rbegin();
        if(res.size() == 0 || res.size() > last - first + 1)
          res = s.substr(first, last - first + 1);
        index_set.erase(first);//更新窗口左边界
        origin.insert(s[first]); //把去掉的窗口左边界的字符重新加入
      }
    }
    return res;
  }
};

/* Solutioin3 整体的滑动窗口策略大方向是没问题的，问题出在了窗口的更新与判断窗口是否包含t上
 * 存在一种可能，去掉左边界后的新窗口以及包含了t，但我的方法还在找下一个和刚去掉的字符
 * 
 * 换言之，我从一开始就没想明白窗口要怎么滑，一个新窗口的判定是这个窗口是否包含了t，而非能找到一个新的更被去掉的
 * 字符
 * 那现在这个题目的聚焦点就清晰了，就是如何判断窗口包含t
 */


class Solution4 {
public:
  string minWindow(string s, string t) {
    int m = s.size(), n = t.size(), less = 0;
    if(m < n || n == 0)
      return "";
    int cnt[128] = {0};
    for(char c : t) { //统计t中各个字符出现的次数
      if(cnt[c] == 0) //当c在t中出现，则有一个字符在空窗口中出现的次数小于t中出现的次数
        less++;       //窗口中有 less 种字母的出现次数小于 t 中字母的出现次数
      cnt[c]++;
    }
    int ansLeft = -1, ansRight = m, left = 0, right = 0;
    for( ; right < m; right++) {
      char c = s[right]; //右端字符
      cnt[c]--; 
      if(cnt[c] == 0) { //该字符在窗口中的出现次数和t中的出现次数相同
        less--;
      }
      while(less == 0) {//当窗口包含t时，更新左端点到不包含t的情况
        if(right - left < ansRight - ansLeft) {
          ansRight = right;
          ansLeft = left;
        }
        char l = s[left];
        if(cnt[l] == 0) { //这个条件说明该字符在窗口中出现的次数和在t中出现的次数相同
          less++;   //于是当窗口移除这个字符时，窗口相比于t，少了一个该字符
        }
        left++;
        cnt[l]++;
      }
    }
    if(ansLeft == -1) return "";
    else return s.substr(ansLeft, ansRight - ansLeft + 1);
  }
};

int main() {
  Solution3 s;
  s.minWindow("ADOBECODEBANC", "ABC");
}