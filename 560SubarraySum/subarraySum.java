import java.util.HashMap;
import java.util.Map;

class Solution {
  public int subarraySum(int[] nums, int k) {
    Map<Integer, Integer> m = new HashMap<>();
    int ans = 0;
    int s = 0;
    m.put(0, 1); //前0项和为0，和为0的前缀和已经有一个了
    for(int i = 0; i < nums.length; i++) {
      s += nums[i];
      ans += m.getOrDefault(s - k, 0);
      m.merge(s, 1, Integer::sum);
    }
    return ans;   
  }
}