import java.util.*;

class Solution {
  public List<Integer> findAnagrams(String s, String p) {
    List<Integer> ans = new ArrayList<>();
    if(s.length() < p.length()) return ans;
    int[] cntP = new int[26], cntS = new int[26];
    for(int i = 0; i < p.length(); i++) {
      cntS[s.charAt(i) - 'a']++;
      cntP[p.charAt(i) - 'a']++;
    }
    for(int left = 0; left < s.length() - p.length(); left++){
      if(Arrays.equals(cntP, cntS)) ans.add(left);
      int right = left + p.length();
      cntS[s.charAt(left) - 'a']--;
      cntS[s.charAt(right) - 'a']++;
    }
    if(Arrays.equals(cntP, cntS)) ans.add(s.length() - p.length());
    return ans;
  }
}