class Solution:
  def moveZeroes(self, nums: List[int]) -> None:
    i = 0
    j = 0
    length = len(nums)
    for i in range(length):
      if nums[i]:
        if(j < i):
          nums[j] = nums[i]
          j = j + 1

    # while(i < length):
    #   if(nums[i] == 0):
    #     i = i + 1
    #   else:
    #     if(j < i):
    #       nums[j] = nums[i]
    #     i = i + 1
    #     j = j + 1
    for i in range(j, length):
      nums[i] = 0

