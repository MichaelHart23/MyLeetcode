import java.util.*;

class Solution {
    public int[][] merge(int[][] intervals) {
        Arrays.sort(intervals, (int[] a, int[] b) -> {
            return a[0] - b[0];
        });
        List<int[]> ans = new ArrayList<>();
        for (int[] x : intervals) {
            int n = ans.size();
            if (ans.isEmpty() || ans.get(n - 1)[1] < x[0]) {
                ans.add(x);
            } else if (ans.get(n - 1)[1] <= x[1]) {
                ans.get(n - 1)[1] = x[1];
            }
        }
        return ans.toArray(new int[ans.size()][]);
    }
}
