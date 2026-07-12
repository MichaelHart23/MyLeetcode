#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        deque<string_view> stk;
        int n = path.size();
        int left = 0, right = 0;
        while (true) {
            while (right < n && path[right] == '/') {
                right++;
            }
            left = right;
            while (right < n && path[right] != '/') {
                right++;
            }
            string_view sv = string_view(path).substr(left, right - left);
            if (sv.size() == 0) {
                break;
            } else if (sv == ".") {
                // it's ok
            } else if (sv == "..") {
                if (!stk.empty()) {
                    stk.pop_back();
                }
            } else {
                stk.push_back(sv);
            }
            left = right;
        }
        if (stk.size() == 0) {
            return "/";
        }
        string res;
        for (auto sv : stk) {
            res += "/";
            res += sv;
        }
        return res;
    }
};
