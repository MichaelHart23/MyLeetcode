# 首先问题可转化为求第k大
# 然后我们知道前k大肯定由两个nums数组的前缀构成，那么第k大的数学形式就是
# f(x) = max(nums1[x],nums2[k - x])。显然第k大是所有f(x)可能取值中的最小值。
# 由高中数学可知，单调增函数和减函数取max的结果f(x)，是个凹函数。
# 三分法秒了。（三分法用于求单峰函数的极大极小值）

# 遇到上坡平肩会错，例子
# nums1 = [4, 5, 10, 10, 10, 10, 10, 10, 10]
# nums2 = [-2, -1, 0, 1, 2, 3, 4, 5, 6]

class Solution:
    def findMedianSortedArrays(self, nums1: list[int], nums2: list[int]) -> float:
        n1, n2 = len(nums1), len(nums2)
        N = n1 + n2 + 1
        nums1.append(-1e9)
        nums2.append(-1e9)
        

        def find_k(k):
            # 解定义域
            # 0 <= i <= n1
            # 0 <= k - i <= n2
            l = max(0, k - n2)
            r = min(k, n1)

            def get_val(i):
                return max(nums1[i-1], nums2[k - i-1])
            # 三分模板
            while r - l > 2:
                m1 = l + (r - l) // 3
                m2 = r - (r - l) // 3
                if get_val(m1) < get_val(m2):
                    r = m2
                else:
                    l = m1
            return min(get_val(i) for i in range(l, r + 1))

        return (find_k(N // 2) + find_k((N + 1) // 2)) / 2