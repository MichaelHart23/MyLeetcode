#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 10000;
int f[101][N + 1];

auto init = [] {
    ranges::fill(f[0], INT_MAX);
    f[0][0] = 0;
    for (int i = 1; i * i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (j < i * i) {
                f[i][j] = f[i - 1][j]; // 只能不选
            } else {
                f[i][j] = min(f[i - 1][j], f[i][j - i * i] + 1); // 不选 vs 选
            }
        }
    }
    return 0;
}();

int ff[N + 1];

auto init2 = [] {
    ranges::fill(ff, INT_MAX);
    ff[0] = 0;
    for (int i = 1; i * i <= N; i++) {
        for (int j = i * i; j <= N; j++) {
            ff[j] = min(ff[j], ff[j - i * i] + 1); // 不选 vs 选
        }
    }
    return 0;
}();

class Solution {
public:
    int numSquares(int n) {
        return f[(int) sqrt(n)][n]; // 也可以写 f[100][n]
    }
};

class Solution {
public:
  int numSquares(int n) {
    vector<int> dp(n + 1);
    for(int i = 0; i < n + 1; i++) dp[i] = i;
    for(int i = 2; ; i++) {
      int square = i * i;
      if(square > n) break;
      for(int j = 1; j < n + 1; j++) {
        if(square > j) continue;
        dp[j] = min(dp[j], dp[j - square] + 1);
      }
    } 
    return dp[n];
  }
};
