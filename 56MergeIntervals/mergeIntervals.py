from typing import List

class Solution:
  def merge(self, intervals: List[List[int]]) -> List[List[int]]:
    intervals.sort(key = lambda p: p[0])
    ans = []
    for it in intervals:
      if not ans or ans[-1][1] < it[0]:
        ans.append(it)
      elif ans[-1][1] <= it[1]:
        ans[-1][1] = it[1]
    return ans

