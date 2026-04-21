import java.util.HashSet;

class Solution {
  public int lengthOfLongestSubstring(String s) {
    int res = 0;
    HashSet<Character> set = new HashSet<>();
    int left = 0;
    for(int i = 0; i < s.length(); i++) {
      while(set.contains(s.charAt(i))){
        set.remove(s.charAt(left));
        left++;
      }
      res = Math.max(res, i - left + 1);
      set.add(s.charAt(i));
    }
    return res;
  }
}