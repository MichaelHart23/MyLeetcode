#include <bits/stdc++.h>

using namespace std;

/**
 * 20260803
 * 我用递归的方式做的，实际上可以直接用栈模拟，更快更简单
 */
class Solution {
    int index;
    int eval(vector<string>& tokens) {
        string token = tokens[index--];
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int right_val = eval(tokens);
            int left_val = eval(tokens);
            if (token == "+") {
                return left_val + right_val;
            } else if (token == "-") {
                return left_val - right_val;
            } else if (token == "*") {
                return left_val * right_val;
            } else if (token == "/") {
                return left_val / right_val;
            }
        } else {
            return stoi(token);
        }
        return -1; // no reach
    }
public:
    int evalRPN(vector<string>& tokens) {
        index = tokens.size() - 1;
        return eval(tokens);
    }
};
