#include <bits/stdc++.h>

using namespace std;

void printArr(vector<int>& v) {
    for (auto i : v) {
        std::cout << i << endl;
    }
}
/**
 * 哪些孩子给一个呢？局部极小值，而要找到局部极小值，就要找局部单调区间
 * 先单调递减后单调递增的局部，但单调递增区间的最后一个孩子给多少还要取决于其下一个单调递减区间
 * 要把它算到下一个单调递减区间里，去计算其糖果数
 *
 * 找到每一段单调区间，每一段区间单独处理
 *
 * 关键洞察是单调区间，实现上一次循环只处理一段单调区间
 */
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        int left = 0;
        vector<int> candies(n, 1);
        // 每次处理一个单调区间，增或减或平
        while (left < n - 1) {
            int cur = left;
            if (cur >= n - 1) {
                break;
            }
            if (ratings[cur] > ratings[cur + 1]) {
                // 如果是一个单调减区间
                while (cur < n - 1 && ratings[cur] > ratings[cur + 1]) {
                    cur++;
                }
                for (int i = cur; i >= left; i--) {
                    candies[i] = cur - i + 1;
                }
                if (left > 0 && ratings[left] > ratings[left - 1]) {
                    candies[left] = max(candies[left - 1], candies[left + 1]) + 1;
                }
                left = cur;
            } else if (ratings[cur] == ratings[cur + 1]) {
                // 如果是一个平区间
                while (cur < n - 1 && ratings[cur] == ratings[cur + 1]) {
                    cur++;
                }
                for (int i = left + 1; i < cur; i++) {
                    candies[i] = 1;
                }
                if (cur == n - 1) {
                    candies[cur] = 1;
                }
                left = cur;
            } else if (ratings[cur] < ratings[cur + 1]) {
                // 如果是一个单调增区间
                while (cur < n - 1 && ratings[cur] < ratings[cur + 1]) {
                    cur++;
                }
                for (int i = left; i <= cur; i++) {
                    candies[i] = i - left + 1;
                }
                left = cur;
            }
        }
        printArr(candies);
        return accumulate(candies.begin(), candies.end(), 0);
    }
};

int main() {
    vector<int> v = {1, 3, 4, 5, 2};
    Solution s;
    s.candy(v);
}