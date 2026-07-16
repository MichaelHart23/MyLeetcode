#include <bits/stdc++.h>

using namespace std;

/**
 * 利用正常罗马数是递减的特性，一旦出现递增就是特殊情况的特性来做
 * 而不是分类讨论
 */
class Solution {
public:
    int romanToInt(string s) {
        int table[26] = {0};
        table['I' - 'A'] = 1;
        table['V' - 'A'] = 5;
        table['X' - 'A'] = 10;
        table['L' - 'A'] = 50;
        table['C' - 'A'] = 100;
        table['D' - 'A'] = 500;
        table['M' - 'A'] = 1000;
        int n = s.size();
        int res = 0;
        for (int i = 0; i + 1 < n; i++) {
            int left = table[s[i] - 'A'], right = table[s[i+1] - 'A'];
            if (left >= right) {
                res += left;
            } else {
                res -= left;
            }
        }
        res += table[s.back() - 'A'];
        return res;
    }
};
