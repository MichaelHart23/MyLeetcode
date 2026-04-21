#include <iostream>
#include <vector>

using namespace std;

int coinChange(vector<int>& coin, int amt) {
  int size = coin.size();
  vector<vector<int>> dp(size + 1, vector<int>(amt + 1, 0));
  int max = amt + 1;
  for(int i = 1; i < amt + 1; i++) {
    dp[0][i] = max;
  }
  for(int i = 1; i < size + 1; i++) {
    for(int amount = 1; amount < amt + 1; amount++) {
      if(coin[i - 1] > amount) {
        dp[i][amount] = dp[i - 1][amount];
      }
      else {
        dp[i][amount] = min(dp[i - 1][amount], dp[i][amount - coin[i - 1]] + 1);
      }
    }
  }
  return dp[size][amt] == max ? -1 : dp[size][amt];
}
int main() {
  vector<int> coins = {1, 2, 5};
  int amt = 11;
  cout << coinChange(coins, amt) << endl;
  return 0;
}