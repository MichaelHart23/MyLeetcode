#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        deque<char> stk;
        auto isPair = [&](char l, char r)->bool {
            return (l == '(' && r == ')') || (l == '[' && r == ']') || (l == '{' && r == '}');
        };
        for(char c : s) {
            if(c == '(' || c == '[' || c == '{') {
                stk.push_back(c);
            } else {
                if(stk.empty()) return false;
                char top = stk.back();
                stk.pop_back();
                if(!isPair(top, c)) return false;
            }
        }
        return stk.empty();
    }
};
