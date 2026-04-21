#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    int size = coins.size();
    for(int i = 1; i < size + 1; i++) {
      for(int num = 1; num < amount + 1; num++) {
        if(coins[i - 1] <= num) dp[num] = min(dp[num], dp[num - coins[i - 1]] + 1);
      }
    }
    return dp[amount] == amount + 1 ? -1 : dp[amount];
  }
};
