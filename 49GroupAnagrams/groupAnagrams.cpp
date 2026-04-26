#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    string s;
    s.assign(26, '0'); //相当于针对小写字符的特化哈希表
    unordered_map<string, vector<string>> map;
    for (string& str : strs) {
        string key(s);
        for (char c : str) { key[c - 'a']++; }
        map[key].push_back(str);
    }
    vector<vector<string>> res;
    res.resize(map.size());
    for (auto& it : map) { res.emplace_back(std::move(it.second)); }
    return res;
}

/**
 * 20260423重做，排了两次序，不如之前上面的方法好，之前的方法好在哪？
 * 
 * 1 区分不同的Anagrams，不用排序，对每个字母进行计数就好. 但当每个单词都很短的时候，可能排序还是好一点
 * 2 能区分不同的Anagrams了，怎么把它们分组呢？用哈希表，而不用再排序了
 */
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int size = strs.size();
        vector<pair<string, int>> ss;
        for(int i = 0; i < size; i++) {
            ss.push_back({strs[i], i});
            sort(ss[i].first.begin(), ss[i].first.end()); //对每个字符串进行排序
        }
        sort(ss.begin(), ss.end()); //对所有排序后的字符串进行排序，用于分组，并记录其在原数组的index
        vector<vector<string>> ans;
        int i = 0;
        while(i < size) {
            vector<string> v;
            v.push_back(strs[ss[i].second]);
            i++;
            while(i < size && ss[i].first == ss[i - 1].first) {
                v.push_back(strs[ss[i].second]);
                i++;
            }
            ans.push_back(move(v));
        }
        return ans;
    }
};

int main() {}