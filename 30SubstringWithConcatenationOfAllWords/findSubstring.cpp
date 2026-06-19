#include <bits/stdc++.h>

using namespace std;

/**
 * 对于这个题目的场景，我有两个疑问：
 * 1 words中的所有单词是不重的吗？不保证不重
 * 2 s中除word以外的单词或字符串的长度和word一样吗？不一定一样
 * 
 * 对于 1，巧妙的运行哈希表，计数缺少的数量，并额外维护一个lack cnt就可以优雅的处理，每次以O(1)的时间复杂度判断当前窗口是否满足条件
 * 对于 2：如果有能把字符串按照单词切分，那也能优雅的处理，甚至需要所有word的长度一样的条件，但那样需要额外的数据结构和代码复杂度
 *        而且字符串s中的单词们也不一定就是标准单词，可能是乱码，所以几乎不能优雅的处理，即几乎不可能在不增加时间复杂度的基础上解决
 *        那怎么处理不定长单词呢？假设答案是存在的，那仍然可以从某个起点开始，维护一个定长窗口，每次跳word len，最终跳到答案
 *        所以要跑word len次滑动窗口，时间复杂度翻了word len倍
 * 
 * 另外，我用了string view来避免拷贝，加快速度
 */
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int word_num = words.size();
        if (word_num == 0) {
            return {};
        }
        int word_len = words[0].size();
        int total_len = s.size();
        if (total_len < word_num * word_len) {
            return {};
        }

        unordered_map<string_view, int> word_cnt_table;
        for (string& s : words) {
            string_view sv = s;
            word_cnt_table[sv]++;
        }
        // word cnt table就是对每个单词，目前窗口内还缺少几个的计数。0表示不缺这个单词，负数表示这个单词多了
        int lack_cnt = word_num;  // 还缺几个单词，目的是以O(1)的时间复杂度判断当前窗口内是否包含所有word
        // 可以说 "lack_cnt == 0" 和 "word cnt table里所有word的计数都为0" 是充要条件

        vector<int> res;

        for (int left = 0; left < word_len; left++) {
            unordered_map<string_view, int> table_copy = word_cnt_table;
            int lack_cnt = word_num;
            for (int i = 0; i < word_num; i++) {
                int start = left + word_len * i;
                string_view sv(s.data() + start, word_len);
                auto it = table_copy.find(sv);
                if (it != table_copy.end()) {
                    if (it->second > 0) {
                        lack_cnt--;
                    }
                    it->second--;
                }
            }
            int start = left;
            int cur = left + word_len * word_num;
            while (true) {
                if (lack_cnt == 0) {
                    res.push_back(start);
                }
                if (cur >= total_len || cur + word_len > total_len) {
                    break;
                }
                string_view s_pop(s.data() + start, word_len);
                auto it_pop = table_copy.find(s_pop);
                if (it_pop != table_copy.end()) {
                    it_pop->second++;
                    if (it_pop->second > 0) {
                        lack_cnt++;
                    }
                }

                string_view s_push(s.data() + cur, word_len);
                auto it_push = table_copy.find(s_push);
                if (it_push != table_copy.end()) {
                    if (it_push->second > 0) {
                        lack_cnt--;
                    }
                    it_push->second--;
                }

                start += word_len;
                cur += word_len;
            }
        }
        return res;
    }
};

int main() {
    string s = "wordgoodgoodgoodbestword";
    vector<string> words = {"word","good","best","good"};
    Solution so;
    so.findSubstring(s, words);
}