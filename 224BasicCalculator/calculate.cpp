#include <bits/stdc++.h>
using namespace std;


/***** 以下是我之前仿照 clox 写的一个递归下降算式解析器 ******/
// It's context free grammar:
// expression → term ( ('+' | '-') term )*
// term       → factor ( ('*' | '/') factor )*
// factor     → '(' expression ')' | number
// number     → '-'? digit+ ('.' digit+)?
//
// 只要定义好了文法(grammar)，那么递归下降写起来就轻轻松松

double factor();
double number();
double term();

std::string expr;
int index = 0;

void skipWhiteSpace() {
    while (expr[index] == ' ') index++;
}

char peek() {
    if (index < expr.length()) return expr[index];
    return 0;
}

char advance() {
    if (index >= expr.length()) return 0;
    index++;
    return expr[index - 1];
}

bool match(char c) {
    if (peek() != c) return false;
    advance();
    return true;
}

double expression() {
    double res = term();
    while (1) {
        skipWhiteSpace();
        int sign = 1;
        char op = peek();
        if (op == '-')
            sign = -1;
        else if (op != '+')
            return res;
        else if (op != '+')
            return res;
        advance();
        res += sign * term();
    }
}

double term() {
    double res = factor();
    while (1) {
        skipWhiteSpace();
        if (match('*')) {
            res *= factor();
        } else if (match('/')) {
            double fac = factor();
            if (fac == 0) {
                std::cout << "divided by zero" << std::endl;
                exit(0);  // error divide by 0
            }
            res /= fac;
        } else
            return res;
    }
}

double factor() {
    skipWhiteSpace();
    if (match('(')) {
        double exp = expression();
        skipWhiteSpace();
        if (!match(')')) {
            std::cout << "expect ')'" << std::endl;
            exit(0);  // error括号不配对
        }
        return exp;
    }
    return number();
}

bool isDigit() {
    char c = peek();
    return (c >= '0') && (c <= '9');
}

double number() {
    skipWhiteSpace();
    int sign = 1;
    if (match('-')) sign = -1;
    int start = index;
    int len = 0;
    while (isDigit()) {
        advance();
        len++;
    }
    if (match('.')) {
        len++;
        while (isDigit()) {
            advance();
            len++;
        }
    }
    double res = sign * stod(expr.substr(start, len));
    return res;
}

int main() {
    // std::getline(std::cin, expr);
    expr = "3/2+4*4-(2+-3+(2*4))";
    double res = expression();
    std::cout << res << std::endl;
}

/**
 * 先不考虑多位数，负数的处理，just treat them as a number（另外，该题目本身不涉及小数）
 * 对括号，将其递归处理，那么也可以把其看作一个number
 * 那么这个算式就被 抽象/简化 成了：由 +/- 连接起来的一些number
 * 这样简化后的算是应该怎么处理？
 * 维护一个num，遍历这一个算式的每一个token，对加减分情况处理就好了
 * it = expr.begin();
 * num = it.value();
 * while (it != end) {
 *   switch it.value()
 *   case +: num += (++it).value(); it++;
 *   case -: num -= (++it).value(); it++;
 * }
 * 
 * 但当首个 number 是 () 的时候，没法办
 * 可以用栈承载结果
 * 接下来一版已经做好了，把算式转换为number，+，-，(，)这五种token。然后利用栈来进行计算就好了。
 */

/**
 * some trick
 * 1 use some variable outside the loop: 'sign', 'num' to represent 之前遇到的 sign and number.
 * 2 Assume there is a sign before every number. 
 *   So you don't need to decide whether '-' is a sign or a  operator
 * 3 deal with digits inside the loop.
 */
class Solution {
public:
    int calculate(string s) {
        int sign = 1;
        long long num = 0;
        stack<int> stk; // when meet a '(', this stack saves the sign and res
        int len = s.size();
        int i = 0;
        auto isDigit = [](char c) {
            return c >= '0' && c <= '9';
        };
        while (i < len) {
            if (isDigit(s[i])) {
                long long curNum = 0;
                while (isDigit(s[i])) {
                    curNum = curNum * 10 + (s[i] - '0');
                    i++;
                }
                num += curNum * sign;
            } else {
                char c = s[i];
                switch (c) {
                    case '+':
                        sign = 1;
                        break;
                    case '-':
                        sign = -1;
                        break;
                    case '(':
                        stk.push(num);
                        stk.push(sign);
                        sign = 1;
                        num = 0;
                        break;
                    case ')': {
                        sign = stk.top();
                        stk.pop();
                        int temp = num;
                        num = stk.top();
                        stk.pop();
                        num += sign * temp;
                        break;
                    }
                    default:  // whitespace
                        break;
                }
                i++;
            }
        }
        return num;
    }
};
