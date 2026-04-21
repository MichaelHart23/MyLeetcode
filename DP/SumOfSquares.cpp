#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> val(10, 0);

char digit[] = "0123456789";

int getTargetSum(int n) {
  int res = 0;
  while(n > 0) {
    int remainder = n % 10;
    res += remainder * remainder;
    n /= 10;
  }
  return res;
}

/**
 * dp数组版实现
 */
string cal(int n) {
  int targetSum = getTargetSum(n);
  vector<vector<string>> dp(10, vector<string>(targetSum + 1));
  for(int i = 1; i < targetSum + 1; i++) {
    dp[0][i] = "#";
  }
  for(int i = 1; i < 10; i++) {
    for(int num = 1; num < targetSum + 1; num++) {
      if(val[i] > num) {
        dp[i][num] = dp[i - 1][num];
      } else {
        string& noSelect = dp[i - 1][num];
        string& select = dp[i][num - val[i]];
        if(noSelect == "#" && select == "#") {
          dp[i][num] = "#";
        } else if(noSelect == "#" || select == "#") {
          dp[i][num] = noSelect == "#" ? select + digit[i] : noSelect;
        } else {
          string can = select + char('0' + i);
          
          if(can.length() != noSelect.length()) {
            dp[i][num] = can.length() < noSelect.length() ? can : noSelect;
          } else {
            dp[i][num] = can < noSelect ? can : noSelect;
          }

        }
      }
    }
  }
  return dp[9][targetSum];
}

/**
 * 空间优化版本
 */
string spaceCal(int n) {
  int targetSum = getTargetSum(n);
  vector<string> dp(targetSum + 1, "#");
  dp[0] = "";
  for(int i = 1; i < 10; i++) {
    for(int num = targetSum; num > 0; num--) {
      if(val[i] > num) continue;
      string& noSelect = dp[num];
      string& select = dp[num - val[i]];
      if(noSelect == "#" && select == "#") {
        dp[num] = "#";
      } else if(noSelect == "#" || select == "#") {
        dp[num] = noSelect == "#" ? select + digit[i] : noSelect;
      } else {
        string can = select + char('0' + i);
        if(can.length() != noSelect.length()) {
          dp[num] = can.length() < noSelect.length() ? can : noSelect;
        } else {
          dp[num] = can < noSelect ? can : noSelect;
        }
      }
    }
  }


  return dp[targetSum];
}


int main() {
  int times = 0;

  for(int i = 1; i < 10; i++) {
    val[i] = i * i;
  }
  cin >> times;
  while(times--) {
    int n;
    cin >> n;
    cout << spaceCal(n) << endl;
  }

}