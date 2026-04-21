#include <bits/stdc++.h>
using namespace std;

/**
 * 思路就是：找两个数组中第 k
 * 个大的元素，所以维护两个指针，使得这两个指针左边的元素个数和是总个数的一半
 * 然后移动这两个指针，移动过程中保持上述性质，也就是方向相反，步长相同
 * 直到，这两个指针右边的元素都大于这两个指针指向的元素，就算找到了
 * 实现起来比较复杂
 *
 * 移动指针的过程可以用二分
 */

// 移动双指针的做法, 分别从两个数组的中间开始向两边查，代码太难写对了
// 因为要讨论两个数组互为奇偶的情况，双奇数和双偶数一开始的一刀切的差别大，一套代码太难处理
// 不如直接统计总数，按照总数除以2来切分
// 因为两个数组分别取中位数那样不能保证能取到总数的中位数，在某些情况下和总数中位数差距较大
// 所以不如直接取总数的中位数，保证双指针所占有的左边的元素的数量始终是中位数
class Solution1 {
  public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证nums1是较短的数组
        if (nums1.size() > nums2.size()) { return findMedianSortedArrays(nums2, nums1); }
        int m = nums1.size();
        int n = nums2.size();
        int total = m + n;
        // k 是中位数在合并后数组中的位置（第 k 小的元素，1-indexed）
        int k = (total + 1) / 2;  // 向上取整

        // 处理其中一个数组为空的情况
        if (m == 0) {
            if (n % 2 == 1)
                return nums2[k - 1];
            else
                return (nums2[k - 1] + nums2[k]) / 2.0;
        }
        if (n == 0) {
            if (m % 2 == 1)
                return nums1[k - 1];
            else
                return (nums1[k - 1] + nums1[k]) / 2.0;
        }
        int l1 = 0, l2 = 0;
        int r1 = nums1.size() - 1, r2 = nums2.size() - 1;
        // 无论两数组的奇偶情况如何，这样都是能找到答案的
        int mid1 = l1 + (r1 - l1) / 2;
        int mid2 = l2 + (r2 - l2) / 2;

        auto get1 = [&](int index) -> int {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums1.size())
                return INT32_MAX;
            else
                return nums1[index];
        };
        auto get2 = [&](int index) {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums2.size())
                return INT32_MAX;
            else
                return nums2[index];
        };
        while (max(get1(mid1), get2(mid2)) > min(get1(mid1 + 1), get2(mid2 + 1))) {
            if (nums1[mid1] > nums2[mid2]) {
                mid1--;
                mid2++;
            } else if (nums1[mid1] < nums2[mid2]) {
                mid1++;
                mid2--;
            } else {
                break;
            }
            // 一旦越界，就已经找到答案了，
            if (mid1 < 0 || mid1 >= nums1.size() || mid2 < 0 || mid2 >= nums2.size()) break;
        }
        double res;
        int even1 = nums1.size() % 2 == 0;
        int even2 = nums2.size() % 2 == 0;
        if (even1 && even2) {  // 双偶越界只能越左边界
            res = (max(get1(mid1), get2(mid2)) + min(get1(mid1 + 1), get2(mid2 + 1))) / 2.0f;
        } else if (!even1 && !even2) {  // 双奇越不了界
            res = (get1(mid1) + get2(mid2)) / 2.0;
        } else {
            res = max(get1(mid1), get2(mid2));
        }
        return res;
    }
};

// 这是别人实现的，按照总数分然后双指针移动的做法
class Solution2 {
  public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证 nums1 是较短的数组，以优化时间复杂度
        if (nums1.size() > nums2.size()) { return findMedianSortedArrays(nums2, nums1); }

        int m = nums1.size();
        int n = nums2.size();
        int total = m + n;
        // k 是中位数在合并后数组中的位置（第 k 小的元素，1-indexed）
        int k = (total + 1) / 2;  // 向上取整

        // 处理其中一个数组为空的情况
        if (m == 0) {
            if (n % 2 == 1)
                return nums2[k - 1];
            else
                return (nums2[k - 1] + nums2[k]) / 2.0;
        }
        if (n == 0) {
            if (m % 2 == 1)
                return nums1[k - 1];
            else
                return (nums1[k - 1] + nums1[k]) / 2.0;
        }

        // 初始划分：取 nums1 的中间位置
        int mid1 = (m + 1) / 2;  // nums1 左半部分的元素个数（向上取整）
        int mid2 = k - mid1;     // nums2 左半部分的元素个数

        // 获取划分点左右两边的值（越界时用极值代替）
        auto getLeft = [](const vector<int>& nums, int idx) -> int { return (idx <= 0) ? INT_MIN : nums[idx - 1]; };
        auto getRight = [](const vector<int>& nums, int idx) -> int {
            return (idx >= (int)nums.size()) ? INT_MAX : nums[idx];
        };

        int l1 = getLeft(nums1, mid1);
        int r1 = getRight(nums1, mid1);
        int l2 = getLeft(nums2, mid2);
        int r2 = getRight(nums2, mid2);

        // 调整划分，直到满足交叉条件
        while (!(l1 <= r2 && l2 <= r1)) {
            if (l1 > r2) {
                // 需要将 nums1 的左半部分减少一个元素
                mid1--;
                mid2++;
            } else if (l2 > r1) {
                // 需要将 nums1 的左半部分增加一个元素
                mid1++;
                mid2--;
            }
            // 更新边界值
            l1 = getLeft(nums1, mid1);
            r1 = getRight(nums1, mid1);
            l2 = getLeft(nums2, mid2);
            r2 = getRight(nums2, mid2);
        }

        int leftMax = max(l1, l2);
        int rightMin = min(r1, r2);

        if (total % 2 == 1) {
            return leftMax;  // 奇数长度，中位数就是左半部分的最大值
        } else {
            return (leftMax + rightMin) / 2.0;  // 偶数长度，取平均值
        }
    }
};

// 我自己实现的按照总数切分然后双指针移动的做法
class Solution3 {
  public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证nums1是较短的数组
        if (nums1.size() > nums2.size()) { return findMedianSortedArrays(nums2, nums1); }
        int m = nums1.size(), n = nums2.size();
        // 用函数来处理越界情况，同时填充 INT_MIN 和 INT_MAX 来保证一致性
        auto get1 = [&](int index) -> int {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums1.size())
                return INT32_MAX;
            else
                return nums1[index];
        };
        auto get2 = [&](int index) -> int {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums2.size())
                return INT32_MAX;
            else
                return nums2[index];
        };
        int i = -1, j = (m + n + 1) / 2 - 1; //双指针本身占据的元素和左边的元素一共是(m+n+1)/ 2个
        while (1) {
            //等价于max(左边两元素) < min(右边两元素)
            if (get1(i) <= get2(j + 1) && get2(j) <= get1(i + 1)) { 
                int maxOf = max(get1(i), get2(j));
                int minOf = min(get1(i + 1), get2(j + 1));  
                return (m + n) % 2 == 0 ? (maxOf + minOf) / 2.0 : maxOf;
            } 
            i++;
            j--;
        }
    }
};

//总数切分，从中间开始双指针查找
class Solution4 {
  public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证nums1是较短的数组
        if (nums1.size() > nums2.size()) { return findMedianSortedArrays(nums2, nums1); }
        int m = nums1.size(), n = nums2.size();
        // 用函数来处理越界情况，同时填充 INT_MIN 和 INT_MAX 来保证一致性
        auto get1 = [&](int index) -> int {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums1.size())
                return INT32_MAX;
            else
                return nums1[index];
        };
        auto get2 = [&](int index) -> int {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums2.size())
                return INT32_MAX;
            else
                return nums2[index];
        };
        int total = (m + n + 1) / 2;
        int mid1 = m / 2 - 1; //指针1本身占据的元素加上其左边的元素一共是 m / 2 个
        int mid2 = total - m / 2 - 1; //指针2是 total - m / 2 个
        //双指针本身占据的元素和左边的元素一共是(m+n+1)/ 2个
        while(true) {
            if (get1(mid1) <= get2(mid2 + 1) && get2(mid2) <= get1(mid1 + 1)) { 
                int maxOf = max(get1(mid1), get2(mid2));
                int minOf = min(get1(mid1 + 1), get2(mid2 + 1));  
                return (m + n) % 2 == 0 ? (maxOf + minOf) / 2.0 : maxOf;
            } else if(get1(mid1) > get2(mid2)) {
                mid1--;
                mid2++;
            } else if(get1(mid1) < get2(mid2)) {
                mid1++;
                mid2--;
            }
        }
    }
};

//总数切分，二分查找, NB!
class Solution5 {
  public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证nums1是较短的数组
        if (nums1.size() > nums2.size()) { return findMedianSortedArrays(nums2, nums1); }
        int m = nums1.size(), n = nums2.size();
        // 用函数来处理越界情况，同时填充 INT_MIN 和 INT_MAX 来保证一致性
        auto get1 = [&](int index) -> int {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums1.size())
                return INT32_MAX;
            else
                return nums1[index];
        };
        auto get2 = [&](int index) -> int {
            if (index < 0)
                return INT32_MIN;
            else if (index >= nums2.size())
                return INT32_MAX;
            else
                return nums2[index];
        };
        int total = (m + n + 1) / 2;
        
        int left = -1, right = m;//开区间
        double res;
        while(left + 1 < right) {
            //双指针本身占据的元素和左边的元素一共是(m+n+1)/ 2个
            int mid1 = left + (right - left) / 2;
            int mid2 = total - (mid1 + 1) - 1;
            if(get1(mid1) <= get2(mid2 + 1) && get2(mid2) <= get1(mid1 + 1)) {
                int maxOf = max(get1(mid1), get2(mid2));
                int minOf = min(get1(mid1 + 1), get2(mid2 + 1));  
                res = (m + n) % 2 == 0 ? (maxOf + minOf) / 2.0 : maxOf;
                break;
            } else if(get1(mid1) > get2(mid2)) {
                right = mid1;
            } else if(get1(mid1) < get2(mid2)) {
                left = mid1;
            }
        }
        return res;
    }
};

int main() {
    Solution5 s;
    vector<int> n1 = {1, 2}, n2 = {3, 4};
    cout << s.findMedianSortedArrays(n1, n2) << endl;
}
