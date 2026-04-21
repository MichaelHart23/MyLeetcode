#include <bits/stdc++.h>

using namespace std;

// class Solution {
// bool isDigit(char c) { return c >= '1' && c <= '9'; }
// public:
// string decodeString(string s) {
// int size = s.size();
// deque<int> stk;
// string res;
// for (int i = 0; i < size; i++) {
// if (isDigit(s[i]))
// stk.push_back(s[i]);
// else if (s[i] == '[') {
// string ss;
// int j = i + 1;
// while (s[j != ']') {
// ss += s[j];
// }
// i = j; //后续for循环会自动给i加上1，从而跳过‘]’
// int num = stk.back() - '0';
// stk.pop_back();
// while (num--) {
// res += ss;
// }
// } else
// res += s[i];
// }
// return res;
// }
// };

class Solution1 {
    bool isDigit(char c) { return c >= '0' && c <= '9'; }

  public:
    string decodeString(string s) {
        int size = s.size();
        int start = 0;
        // start传的是引用，全局共享，或许不用传引用，之间在外面声明一个就好，仍旧是所有闭包全局共享
        // 一个递归单元处理一个中括号内的字符串，
        auto recur = [&](auto&& self) -> string {  // c++23前的闭包递归写法
            string res;
            int lastNum = 0;
            while (start < size) {
                if (isDigit(s[start])) {  // 数字可能不止一位
                    while (isDigit(s[start])) {
                        lastNum = lastNum * 10 + s[start] - '0';
                        start++;
                    }
                } else if (s[start] == '[') {
                    start += 1;
                    string ss = self(self);  // c++23前的闭包递归写法：递归调用
                    while (lastNum) {        // 不能写while(lastNum--)，这样lastNum会变成-1
                        res += ss;
                        lastNum--;
                    }
                } else if (s[start] == ']') {
                    start++;
                    return res;
                } else
                    res += s[start++];
            }
            return res;
        };
        return recur(recur);  // c++23前的闭包递归写法
    }
};

/**
 * 栈写法
 * 在写之前，没有好好思考整体设计：没有想明白每个递归单元要做什么已经如何对应到栈上
 * 于是写出一坨来，失败了
 */
class Solution2 {
    bool isDigit(char c) { return c >= '0' && c <= '9'; }
    bool isAlpha(char c) { return c >= 'a' && c <= 'z'; }
public:
    string decodeString(string s) {
        int size = s.size();
        int start = 0;
        stack<string> stk;
        stack<string> preStr;
        string res;
        while (start < size) {
            if (isDigit(s[start])) {  // 数字可能不止一位
                string num = "";
                while (isDigit(s[start])) {
                    num += s[start++];
                }
                stk.push(move(num));
            } else if(s[start] == '[') {
                string str;
                start++;
                while(isAlpha(s[start])) {
                    str += s[start++];
                }
                if(s[start] != ']') {
                    preStr.push(move(str));
                } else stk.push(move(str));
            } else if(s[start] == ']') {
                start++;
                string str(move(stk.top()));
                stk.pop();
                string num(move(stk.top()));
                stk.pop();
                string ss;
                int n = stoi(num);
                while(n--) {
                    ss += str;
                }
                if(!preStr.empty()) {
                    stk.push(move(preStr.top() + ss));
                    preStr.pop();
                } else res += ss;
            } else if(isAlpha(s[start])) {
                string str;
                while(isAlpha(s[start])) {
                    str += s[start++];
                }
                stk.top() += str;
            }
        }
        return res;
    }
};

/**
 * 如何将递归改写成栈写法呢？
 * 观察递归的栈帧，每一个栈帧存着什么东西，每一个“栈单元”就要存什么东西
 * 每一个递归栈帧要解决什么事情
 * 把两者对应上
 * 对于该题目：
 * 每一个递归栈帧要解决的事情是：解析完一个中括号内的内容，并把解析完的内容返回
 * 注意：原来的总字符串也可以看作包裹在一个中括号内的，也是一个递归单元要解决的
 * 每一个栈帧要存的有的就是其要返回的结果字符串，不断填充该字符串就好了，等碰到']'就意味着该栈帧结束
 * 可能其前面还有数字，也可能是原字符串前面没有数字
 */
class Solution {
private:
    bool isDigit(char c) { return c >= '0' && c <= '9'; }
    bool isAlpha(char c) { return c >= 'a' && c <= 'z'; }
public:
    string decodeString(string s) {
        int size = s.size(), i = 0;
        stack<string> stk;
        stk.push(""); //栈底即最终结果
        while(i < size) {
            if(isAlpha(s[i])) {
                while(isAlpha(s[i]) && i < size) {
                    stk.top() += s[i++];
                }
            } else if(isDigit(s[i])) {
                string num;
                while(isDigit(s[i])) {
                    num += s[i++];
                }
                stk.push(num);
                //跳过左括号
                i++;
                //把该递归单元的的返回结果压入栈
                stk.push("");
            } else if(s[i] == ']') {
                i++; //跳过右括号
                string str(move(stk.top()));
                stk.pop();
                string num(move(stk.top()));
                stk.pop();
                int n = stoi(num);
                while(n--) stk.top() += str;
            }
        }
        return stk.top();
    }
};
int main() {
    string str = "3[a]2[bc]";
    string str2;
    Solution s;
    s.decodeString(str);
}
