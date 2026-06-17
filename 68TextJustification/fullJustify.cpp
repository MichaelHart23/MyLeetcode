#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int n = words.size();
        int word_num = 0;
        int total_len = 0;
        int cur_word = 0;
        while (true) {
            word_num++;
            total_len += words[cur_word].size();
            if (total_len + word_num - 1 > maxWidth) {
                word_num--;
                total_len -= words[cur_word].size();
                int start_word = cur_word - word_num;
                int space_num = maxWidth - total_len;
                if (word_num == 1) {
                    word_num = 2;  // 防止除0报错，不会出现问题的，能正确的只填入一个单词
                }
                int common_space = space_num / (word_num - 1);
                int extra_space = space_num % (word_num - 1);
                string line(maxWidth, ' ');
                int cur = 0;
                for (int i = start_word; i < cur_word; i++) {
                    int the_word_len = words[i].size();
                    for (int j = 0; j < the_word_len; j++) {
                        line[cur++] = words[i][j];
                    }
                    if (i == cur_word - 1) {
                        break;
                    }
                    cur += common_space;
                    if (extra_space > 0) {
                        cur += 1;
                        extra_space--;
                    }
                }

                res.push_back(std::move(line));

                word_num = 0;
                total_len = 0;
                continue;
            }
            cur_word++;
            if (cur_word >= n) {
                string line(maxWidth, ' ');
                int cur = 0;
                int start_word = cur_word - word_num;
                for (int i = start_word; i < cur_word; i++) {
                    int the_word_len = words[i].size();
                    for (int j = 0; j < the_word_len; j++) {
                        line[cur++] = words[i][j];
                    }
                    cur += 1;
                }
                res.push_back(std::move(line));
                break;
            }
        }
        return res;
    }
};

int main() {
    vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
    Solution s;
    s.fullJustify(words, 16);
}