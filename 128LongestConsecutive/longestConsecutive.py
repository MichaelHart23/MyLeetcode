class Solution:
  def longestConsecutive(self, nums: List[int]) -> int:
    st = set(nums)
    res = 0
    len_st = len(st)
    for n in st:
      if(n - 1 in st):
        continue
      length = 1
      while(n + length in st):
        length = length + 1
      res = max(length, res)
      if res * 2 > len_st:
        break 
    return res
