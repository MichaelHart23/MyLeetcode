/**
 * 时间复杂度：O(log(min(m,n)))
 * 空间复杂度：O(1)
 * 研究了5天。借鉴了官方和一些比较火的题解，最后在结合自己的想法总结出来，其实这道题不难，只是很多地方的解释会比较复杂深奥，让你感觉很难。
 *
 * 这道题其实就是求第 k 个大的元素
 *
 * 解题步骤：
 * 1、代码中唯一要做的事情就是让 nums1 的前 m 个元素和 nums2 的前 n 个元素数量相加刚好等于 k
 * 2、并且前 m 个元素和前 n 个元素刚好小于等于第 k 个元素
 * 3、满足以上这两个条件，就可以直接求出答案了
 *
 * 提示：
 * 如果 nums1 + nums2 刚好是奇数，则 k 就是 Max(m,n)，如果是偶数 k 就是 Max(m,n) 和它后面一位元素的平均值
 */
var findMedianSortedArrays = function (nums1, nums2) {
    /**
     * 确保时间复杂度达到 min(nums1, nums2)
     * 永远优先处理数组长度短的那个
     */
    if (nums1.length > nums2.length) {
        return findMedianSortedArrays(nums2, nums1)
    }

    /**
     * 处理边界情况，至少两个数组都要有值
     * [][]
     * [][1]
     * [1][]
     */
    if (nums1.length + nums2.length === 0) return []

    if (nums1.length === 0 || nums2.length === 0) {
        let res = nums1.length === 0 ? nums2 : nums1 // 指针指向，不算空间

        const k = Math.ceil((nums1.length + nums2.length) / 2)

        return res.length % 2 === 0 ? (res[k - 1] + res[k]) / 2 : res[k - 1]
    }

    /**
     * 新数组长度是奇数时，k - 1 代表是中位数的索引，为偶数时，k 和 k - 1 代表中位数左右两边的索引
     * k = m + n
     *
     * 这里会比较难理解一点，为什么要有 m 和 n
     * 我们按实际例子来解释，就会容易理解一点
     * 能走到这一步的代码，代表了，nums1 和 nums2 分别是如下结果
     *
     * nums1: 1 3 4 9
     * nums2: 1 2 3 4 5 6 7 8 9 10
     *
     * 不要问为什么 nums1 和 nums2 顺序反了
     * 上面数组合并后长度为 14，因为 k 是 7，所以 n + m 一定是等于 7
     * 那我们就先从短的那个先动手，从中间位置开始动手，比从 0 开始划算
     * 所以先找到 nums1 的中位数，然后在根据 k 推算出 nums2 的大概的中位数（不需要那么准确，后面会挪动位置的，但是记得 k = m + n）
     * 得出 m = 2， n = 5，这里指的不是索引，-1 之后的才是索引位置
     * 然后开始划分
     * 
     * nums1: 1 3 / 4 9
     * nums2: 1 2 3 4 5 / 6 7 8 9 10
     * 
     * 两个数组都划分好了，我们核心是左半部分，右半部分完全不用管
     * 这四部分，分别用 l1 r1 l2 r2 来表示
     * 在回顾一下，我们要做的事情，就是让 l1 + l2 的元素个数达到 k，目前其实是成立的，但是第二个条件 l1 和 l2 的元素要小于等于第 k 个元素，这里是不成立的。
     * 可能肉眼不容易看出来第 k 个元素是谁，但是可以换算一下，就是左半部分完全小于右半部分，目前 l2 并不是全部元素都小于 r1 的全部元素。
     * 所以要挪动位置，以下代码中的 while 就是做挪动的功能
     * l1 大于 r2 那么就让 m 的索引 -1 同时 n 的索引 +1
     * l2 大于 r1 那么就让 n 的索引 -1 同时 m 的索引 +1
     * 一定要一加一减，这样才能让左半部分的数量刚好是 k
     * 
     * 所以执行一次 while 后划分如下
     * 
     * nums1: 1 3 4 / 9
     * nums2: 1 2 3 4 / 5 6 7 8 9 10
     * 
     * 移动一次后，满足条件了，如果不满足就继续移动好了。
     * 
     */
    const k = Math.ceil((nums1.length + nums2.length) / 2) // 7
    let m = Math.ceil(nums1.length / 2) // 2
    let n = k - m // 5

    /**
     * 获取 nums1 索引 m 左右两边的值
     * 获取 nums2 索引 n 左右两边的值
     */
    let l1 = nums1[m - 1] ?? -Infinity
    let r1 = nums1[m] ?? Infinity
    let l2 = nums2[n - 1] ?? -Infinity
    let r2 = nums2[n] ?? Infinity

    /**
     * 判断前 m 个元素和前 n 个元素是否小于等于 k，如果不小于等于 k，则大家都挪动1个位置后继续判断，直到挪到尽头或者小于 k 为止
     */
    while (!(l1 <= r2 && l2 <= r1)) {
        debugger
        if (l1 > r2) {
            m--
            n++
        }

        if (l2 > r1) {
            m++
            n--
        }

        if (l1 > r2 || l2 > r1) {
            // 挪动位置后，要更新一下 m 和 n 前后的元素
            l1 = nums1[m - 1] ?? -Infinity
            r1 = nums1[m] ?? Infinity
            l2 = nums2[n - 1] ?? -Infinity
            r2 = nums2[n] ?? Infinity
        }
    }

    /**
     * 获取中位数 k 左边最大值和右边最小值
     */
    const lmax = Math.max(l1, l2)
    const rmin = Math.min(r1, r2)

    if ((nums1.length + nums2.length) % 2 === 1) {
        return lmax
    }

    if ((nums1.length + nums2.length) % 2 === 0) {
        return (lmax + rmin) / 2
    }
}

const res = findMedianSortedArrays([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 3, 4, 9])