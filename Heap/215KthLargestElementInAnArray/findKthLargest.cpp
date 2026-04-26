#include <bits/stdc++.h>

using namespace std;

//标准库最大堆做法
class Solution1 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> maxHeap; //默认最大堆
        priority_queue<int, vector<int>, greater<int>> minHeap; //最小堆
        for(int i : nums) {
            maxHeap.push(i);
        }
        for(int i = 0; i < k - 1; i++) {
            maxHeap.pop();
        }
        return maxHeap.top();
    }
};

/**
 * 快排做法：快速选择 or 局部快排
 * 我的这种写法面对大量重复元素会超时
 */
class Solution2 {
    int quickSort(vector<int>& v, int left, int right) {
        int pivot = left + rand() % (right - left + 1); //随机选择
        int i = left, j = left; //j遍历整个数组，i记录有几个比pivot小的元素
        //把所有比pivot小的放到左边，大于等于pivot的放到右边
        for(; j <= right; j++) {
            //记录pivot被换到哪里去了,当pivot是右边界的时候无需记录，因为它始终在哪里
            //但当pivot是随机值的时候，它可能会被换来换去，所以就需要记录
            if(v[j] < v[pivot]) {
                if(i == pivot) pivot = j;
                swap(v[j], v[i]); 
                i++;
            }
        }
        swap(v[i], v[pivot]);
        return i;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        srand(time(NULL)); //随机数种子
        int size = nums.size();
        int target = size - k;
        int left = 0, right = size - 1;
        while(true) {
            int i = quickSort(nums, left, right);
            if(i == target) return nums[i];
            if(i < target) {
                left = i + 1;
            } else {
                right = i - 1;
            }
        }
    }
};

//三路分区迭代写法，一路小于，一路等于，一路大于，这样对大量重复元素的抵抗就强,
class Solution3 {
public:
    int findKthLargest(vector<int>& nums, int k) {
        srand((unsigned)time(nullptr));
        int n = nums.size();
        int target = n - k; // 第 target 小

        int l = 0, r = n - 1;
        while (l <= r) {
            int p = l + rand() % (r - l + 1);
            int pivot = nums[p];

            // Dutch National Flag: [l..lt-1] < pivot, [lt..gt] == pivot, [gt+1..r] > pivot
            int lt = l, i = l, gt = r;
            while (i <= gt) {
                if (nums[i] < pivot) swap(nums[i++], nums[lt++]);
                else if (nums[i] > pivot) swap(nums[i], nums[gt--]);
                else i++;
            }

            if (target < lt) r = lt - 1;
            else if (target > gt) l = gt + 1;
            else return nums[target]; // 落在等于 pivot 的区间
        }
        return -1; // 理论不会到这里
    }
};

/**
 * 三路分区 + 相向双指针
 * 这tm才叫相向双指针
 * 比pivot小的存到l那里，比pivot大的存到r那里
 */
class Solution4 {
    pair<int, int> quickSort(vector<int>& v, int left, int right) {
        int pivot = v[left + rand() % (right - left + 1)]; //随机选择
        int l = left, r = right;
        int i = left;
        //[left, l):小于pivot； [l, r]：等于pivot； (r, right]：大于pivot
        while(i <= r) {
            if(v[i] < pivot) {
                swap(v[i], v[l]);
                l++;
                i++;
            } else if(v[i] > pivot) {
                swap(v[i], v[r]);
                r--;
            } else i++;
        }
        return {l ,r};
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        srand(time(NULL)); //随机数种子
        int size = nums.size();
        int target = size - k;
        int left = 0, right = size - 1;
        while(true) {
            auto [i, j] = quickSort(nums, left, right);
            if(j < target) {
                left = j + 1;
            } else if(i > target) {
                right = i - 1;
            } else {
                return nums[i];
            }
        }
    }
};

//三路分区 + 相向双指针 + 随机选取元素的快排写法：
void quickSort(vector<int>& v, int left, int right) {
    if(left >= right) return;
    int pivot = v[left + rand() % (right - left + 1)];  // 随机选择
    int l = left, r = right;
    int i = left;
    //[left, l):小于pivot； [l, r]：等于pivot； (r, right]：大于pivot
    while (i <= r) {
        if (v[i] < pivot) {
            swap(v[i], v[l]);
            l++;
            i++;
        } else if (v[i] > pivot) {
            swap(v[i], v[r]);
            r--;
        } else
            i++;
    }
    quickSort(v, left, l - 1);
    quickSort(v, r + 1, right);
}


//迭代写法快排
void quickSort3(vector<int>& v) {
    int left = 0, right = v.size() - 1;
    deque<pair<int, int>> dq; //一组l r
    dq.push_back({left, right});
    while(!dq.empty()) {
        auto [l, r] = dq.back();
        dq.pop_back();
        if(l >= r) continue;
        //保存当前子数组的边界
        int ll = l;
        int rr = r;
        int pivot = v[l + rand() % (r - l + 1)];  // 随机选择
        int i = l;
        //[left, l):小于pivot； [l, r]：等于pivot； (r, right]：大于pivot
        while(i <= r) {
            if (v[i] < pivot) {
                swap(v[i], v[l]);
                i++;
                l++;
            } else if (v[i] > pivot) {
                swap(v[i], v[r]);
                r--;
            } else
                i++;
        }
        dq.push_back({ll, l - 1});
        dq.push_back({r + 1, rr});
    }
}

//随机选取元素的写法没错
void quickSort1(vector<int>& v, int left, int right) {
    if(left >= right) return;
    int pivot = left + rand() % (right - left + 1);  // 随机选择
    int i = left, j = left;                          // j遍历整个数组，i记录有几个比pivot小的元素
    // 把所有比pivot小的放到左边，大于等于pivot的放到右边
    for (; j <= right; j++) {
        // 记录该元素被换到哪里去了,当pivot是右边界的时候无需记录，因为它始终在哪里
        // 但当pivot是随机值的时候，它可能会被换来换去，所以就需要记录
        if (v[j] < v[pivot]) {
            if (i == pivot) pivot = j;
            swap(v[j], v[i]);
            i++;
        }
    }
    swap(v[i], v[pivot]);
    quickSort(v, left, i - 1);
    quickSort(v, i + 1, right);
}

//随机选取 + 相向双指针
void quickSort2(vector<int>& v, int left, int right) {
    if(left >= right) return;
    int pivot = left + rand() % (right - left + 1);  // 随机选择
    swap(v[left], v[pivot]); //把pivot提前换到开头，防止它被换来换去
    int i = left + 1, j = right; //相向双指针
    // 把所有比pivot小的放到左边，大于等于pivot的放到右边
    while(i < j) {
        //不能交错，一旦交错就定位不了pivot该在的位置了
        while (i < j && v[i] < pivot) i++;
        while (i < j && v[j] > pivot) j--;
        if(i >= j)
        if(v[j] < v[left]) {
            swap(v[i], v[j]);
            j--;
        }
        if(v[i] >= v[left]) {
            swap(v[i], v[j]);
            j--;
        }
    }
    for (; j <= right; j++) {
        // 记录该元素被换到哪里去了,当pivot是右边界的时候无需记录，因为它始终在哪里
        // 但当pivot是随机值的时候，它可能会被换来换去，所以就需要记录
        if (v[j] < v[pivot]) {
            if (i == pivot) pivot = j;
            swap(v[j], v[i]);
            i++;
        }
    }
    swap(v[i], v[pivot]);
    quickSort(v, left, i - 1);
    quickSort(v, i + 1, right);
}

void printVector(vector<int>& v) {
    for(int i : v) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    vector<int> v = {9, 5, 6, 4, 1, 3, 7, 2, 8, 10};
    quickSort3(v);
    printVector(v);
}
