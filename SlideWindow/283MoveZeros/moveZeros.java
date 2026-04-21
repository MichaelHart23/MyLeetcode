
class Solution {
    public void moveZeroes(int[] nums) {
      int i = 0, j = 0;
      int length = nums.length;
      while(i < length) {
        if(nums[i] == 0) {
          i++;
        } else {
          if(j < i) {
            nums[j] = nums[i];
          }
          i++;
          j++;
        }
      }
      for(i = j; i < length; i++) {
        nums[i] = 0;
      }
    }
}