import java.util.*;

class Solution {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for(String str : strs) {
          char[] sorted = str.toCharArray();
          Arrays.sort(sorted);
          String key = new String(sorted);
          map.computeIfAbsent(key, k->new ArrayList<>()).add(str);
        }
        return new ArrayList<>(map.values());
    }
}
