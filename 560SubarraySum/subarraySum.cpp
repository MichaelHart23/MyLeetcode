#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return 0;
        int ans = 0;
        vector<int> s(n + 1);
        s[0] = 0;
        for (int i = 0; i < n; i++) {  // 前缀和
            s[i + 1] = s[i] + nums[i];
        }
        unordered_map<int, int> m;
        for (int i = 0; i < n + 1; i++) {  // 找差为目标值的两个前缀和
            ans += m.contains(s[i] - k) ? m[s[i] - k] : 0;
            m[s[i]]++;
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums = {1, 2, 3};
    s.subarraySum(nums, 3);
}