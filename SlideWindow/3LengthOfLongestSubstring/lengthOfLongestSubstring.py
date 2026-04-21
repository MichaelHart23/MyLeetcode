class Solution:
  def lengthOfLongestSubstring(self, s: str) -> int:
    left, res, size = 0, 0, len(s)
    set_ = set()
    for i in range(0, size):
      while s[i] in set_:
        set_.remove(s[left])
        left += 1
      res = max(res, i - left + 1)
      set_.add(s[i])
    return res
        