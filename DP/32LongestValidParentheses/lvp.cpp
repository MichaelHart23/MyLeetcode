#include <vector>
#include <ranges>
#include <string>
#include <stack>

using namespace std;

//错位做法
class Solution {
public:
    /**
     * dp[i]表示以s[i]结尾的最长有效括号的长度
     * 但还需记录等待配对的左括号个数
     */
    int longestValidParentheses(string s) {
        int size = s.size();
        //dpLen[i]表示以第i个字符为结尾的最长有效括号有多长
        vector<int> dpLen(size + 1, 0);
        //dpLeft[i]表示前i个字符有多少未配对的左括号
        vector<int> dpLeft(size + 1, 0);
        for(int i = 1; i < size + 1; i++) {
            if(s[i - 1] == '(') {
                dpLen[i] = 0;
                dpLeft[i] = dpLeft[i - 1] + 1;
            }
            else if(s[i - 1] == ')') {
                if(dpLeft[i - 1] > 0) {
                    dpLen[i] = max(dpLen[i - 1], dpLen[i - 2]) + 2;
                    dpLeft[i] = dpLeft[i - 1] - 1;
                } else {
                    dpLen[i] = 0;
                }
            }
        }
        return ranges::max(dpLen);
    }
};

/**
 * dp[i]表示以s[i]结尾的最长有效括号的长度
 * 
 * 首先需要知道未匹配的左括号的信息，这样当遍历到右括号时就能知道有没有待匹配的左括号
 * 那直接整一个记录未匹配的左括号的数量的dp数组可以吗？
 * 不行，()(()) 和 ()()  像这些情况都处理不了
 * 
 * 观察/注意到以下情况：
 * 1 当一个右括号和一个左括号进行匹配之后，他们两个之间的括号们一定是有效的
 * 2 他们之前可能也有匹配的括号
 * 对于1的证明，若是多了一个左括号或右括号，那么他们两个绝不可能匹配上
 * 对于2，状态转移方程用的就是这个：dp[i]需要包括两个括号之间的字符数以及他们前面的可能匹配的括号
 * 
 * 基于以上观察，这么设计dp数组：
 * dpLen: dpLen[i]表示以第i个字符结尾的最长有效括号的长度
 * 注意到以左括号结尾不可能构成有效括号
 * 
 * dpLeftList: dpLeftList[i]表示站在第i个字符的视角看，上一个未匹配的左括号是第几个字符
 * 
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        int size = s.size();
        //dpLen[i]表示以第i个字符为结尾的最长有效括号有多长
        vector<int> dpLen(size + 1, 0);

        //dp[i]表示站在第i个字符的角度看，上一个需要被匹配的左括号是第几个字符
        vector<int> dpLeftList(size + 1, 0);
        for(int i = 1; i < size + 1; i++) {
            if(s[i - 1] == '(') {
                dpLen[i] = 0;
                dpLeftList[i] = i;
            }
            else if(s[i - 1] == ')') {
                if(dpLeftList[i - 1] != 0) { //有未匹配的左括号
                    int lastLeft = dpLeftList[i - 1]; //该未匹配的左括号是第几个字符
                    dpLen[i] = i - lastLeft + 1 + dpLen[lastLeft - 1]; //计算两个括号之间的字符数以及他们前面的可能匹配的括号
                    dpLeftList[i] = dpLeftList[lastLeft - 1]; //站在当前遍历到右括号视角看，上一个未匹配的左括号是第几个字符
                } else { //没有未匹配的左括号
                    dpLen[i] = 0;
                }
            }
        }
        return ranges::max(dpLen);
    }
};


/**
 * 0x3f的炸弹栈做法
 */
class Solution {
public:
  int longestValidParentheses(string s) {
    int size = s.size(), res = 0;
    //栈的最底层记录着截止到哪里，不可能构成有效括号了，也就是上一个未匹配的右括号的下标
    stack<int> stk;
    stk.push(-1); // 虚拟红线（哨兵） 
    for(int i = 0; i < size; i++) {
      if(s[i] == '(') {
        stk.push(i);
      } else if(s[i] == ')') {
        if(stk.size() > 1) { //有未匹配的左括号
          stk.pop();
          res = max(res, i - stk.top());
        } else { //没有未匹配的左括号了，更新红线
          stk.top() = i; 
        }
      }
    }
    return res;
  }
};
