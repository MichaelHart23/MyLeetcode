import java.util.HashSet;

class Solution {
  public int longestConsecutive(int[] nums) {
    HashSet<Integer> st = new HashSet<>();
    for(int i : nums) {
      st.add(i);
    }
    int res = 0;
    for(int i : st) {
      if(st.contains(i - 1)) {
        continue;
      }
      int len = 1;
      while(st.contains(i + len)) {
        len++;
      }
      res = Math.max(res, len);
    }
    return res;
  }
}