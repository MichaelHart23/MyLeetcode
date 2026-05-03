#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        res.reserve(1 << n);  // 2^n个子集
        vector<int> state;
        auto backtracking = [&](this auto&& backtracking, int num, int begin) {
            if (state.size() == num) {
                res.push_back(state);
                return;
            }
            for (int i = begin; i < n; i++) {
                state.push_back(nums[i]);
                backtracking(num, i + 1);
                state.pop_back();
            }
        };
        for (int i = 0; i <= n; i++) {  // 元素数为 0-n 的子集
            backtracking(i, 0);
        }
        return res;
    }
};

/**
 * 使用位运算的方式枚举子集
 */
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans(1 << n);  // 1 << n: 2^n个子集
        // 把每个元素看作一位，这样全集就是n位的1，也就是2^n - 1
        // 可以用从0加到2^n - 1方式枚举所有子集 (真巧妙，二进制加法恰好枚举了所有子集)
        for (int i = 0; i < (1 << n); i++) {  // 枚举全集 U 的所有子集 i
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) {  // j 在集合 i 中
                    ans[i].push_back(nums[j]);
                }
            }
        }
        return ans;
    }
};

/**
 * 元素数为n的集合，对于每个元素来说，有选或不选两种可能，那么一共就有2^n个子集
 * 可以依照这个思路去枚举子集
 */
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        vector<int> state;
        // 选或不选nums[i]
        auto dfs = [&](this auto&& dfs, int i) {
            if (i == n) {  // 全部元素的选或不选都已经讨论过了
                res.push_back(state);
                return;
            }
            // 不选nums[i]
            dfs(i + 1);
            // 选nums[i]
            state.push_back(nums[i]);
            dfs(i + 1);
            state.pop_back();
        };
        dfs(0);
        return res;
    }
};
