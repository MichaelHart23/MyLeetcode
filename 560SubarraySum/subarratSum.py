from collections import defaultdict

class Solution:
  def subarraySum(self, nums: List[int], k: int) -> int:
    s, ans = 0, 0
    m = defaultdict(int)
    m[0] = 1
    for i in range(0, len(nums)):
      s += nums[i]
      ans += m[s - k]
      m[s] += 1
    return ans
        