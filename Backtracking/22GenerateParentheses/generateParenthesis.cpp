#include <vector>
#include <string>

using namespace std;

/**
 * 每个位置选左括号还是右括号
 */
class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    int remainLeft = n, remainRight = n;
    int unMatch = 0;
    string str(2 * n, 'a');
    // 对于每一个位置，选左括号或者右括号。当unMath > 0时才能选右括号
    auto dfs = [&](this auto &&dfs, int index)
    {
      if (index == 2 * n)
      {
        res.push_back(str);
        return;
      }
      if (remainLeft > 0)
      {
        str[index] = '(';
        remainLeft--;
        unMatch++;
        dfs(index + 1);
        remainLeft++;
        unMatch--;
      }

      if (remainRight > 0 && unMatch > 0)
      {
        str[index] = ')';
        remainRight--;
        unMatch--;
        dfs(index + 1);
        remainRight++;
        unMatch++;
      }
    };
    dfs(0);
    return res;
  }
};

/**
 * 关键是左括号的位置，只要枚举完左括号的位置，剩下的位置都填充右括号就好了
 * n对括号，左括号可能出现的下标：0 到 2n－2
 * 
 * 怎么枚举左括号的位置呢？
 * 假设已经有了5个左括号和2个右括号，在放下一个左括号之前，还能放3个右括号
 * 那么枚举接下来放几个右括号，其之后的位置就是左括号的位置
 */

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;
    //string str;
    vector<int> lefts; //记录左括号位置的数组
    //为什么用左括号数组而不是一个string来记录当前填充的字符串的信息呢？
    //因为用string的话，加了多个括号再复原开销比较大
    //反而用一个记录左括号位置的数组就能完全表示当前填充括号情况的信息

    int leftNum = 0, rightNum = 0;
    // 当前填了leftNum个左括号和rightNum个右括号
    auto dfs = [&](this auto&& dfs, int leftNum, int rightNum) {
      if(leftNum == n) {
        string temp(2 * n, ')');
        for(int i : lefts) {
          temp[i] = '(';
        }
        res.push_back(move(temp));
        return;
      }
      int nums = leftNum + rightNum; // 一共填了几个括号了
      int diff = leftNum - rightNum; // 左括号比右括号多几个
      for(int i = 0; i <= diff; i++) { //遍历接下来要填的右括号的数量
        //先填了i个右括号，又填了1个左括号
        lefts.push_back(nums + i);  // 当填了i个右括号时，下一个左括号的位置是num+i
        dfs(leftNum + 1, rightNum + i); 
        lefts.pop_back();
      }
    };
    dfs(0, 0);
    return res;
  }
};
