class Solution:
  def threeSum(self, nums: List[int]) -> List[List[int]]:
    nums.sort()
    res = []
    for k in range(0, len(nums) - 2):
      if nums[k] > 0: break
      if k > 0 and nums[k] == nums[k - 1]: continue
      i, j = k + 1, len(nums) - 1
      while i < j:
        sum = nums[k] + nums[i] + nums[j]
        if sum > 0 :
          while i < j and nums[j] == nums[j - 1]: j -= 1
          j -= 1
        elif sum < 0:
          while i < j and nums[i] == nums[i + 1]: i += 1
          i += 1
        else :
          res.append([nums[k], nums[i], nums[j]])
          while i < j and nums[j] == nums[j - 1]: j -= 1
          j -= 1
          while i < j and nums[i] == nums[i + 1]: i += 1
          i += 1
    return res

        

