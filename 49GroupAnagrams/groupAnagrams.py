from collections import defaultdict
from typing import List

# 使用排序后单词的作为键值
def groupAnagrams(strs: List[str]) -> List[List[str]]:
  map = defaultdict(list)
  for s in strs:
    key = ''.join(sorted(s))
    map[key].append(s)
  return list(map.values())
