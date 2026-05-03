#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void swap(int& a, int& b) {
        int c = a;
        a = b;
        b = c;
    }

    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        for (int i = 0; i < n / 2; i++) {
            swap(nums[i], nums[n - 1 - i]);
        }
        for (int i = 0; i < k / 2; i++) {
            swap(nums[i], nums[k - 1 - i]);
        }
        for (int i = k; i < k + (n - k) / 2; i++) {
            swap(nums[i], nums[k + n - 1 - i]);
        }
    }

    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        auto reverse = [&](int i, int j) {
            while (i < j) {
                swap(nums[i++], nums[j++]);
            }
        };
        reverse(0, n - 1);
        reverse(0, k - 1);
        reverse(k, n - 1);
    }
};

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        std::reverse(nums.begin(), nums.end());
        int left = 0, right = k - 1;
        while(left < right) {
            swap(nums[left++], nums[right--]);
        }
        left = k, right = n - 1;
        while(left < right) {
            swap(nums[left++], nums[right--]);
        }
    }
};

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if (!(k %= n)) return;
        int len = n / gcd(n, k); //走几步回到自身，也是循环子群的大小
        int times = n / len; //有几个循环子群
        for (int i = 0; i < times; ++i) {
            int prev = nums[i], next, tmp, cur = i;
            for (int j = 0; j < len; ++j) {
                next = (cur + k) % n;
                tmp = nums[next];
                nums[next] = prev;
                prev = tmp;
                cur = next;
            }
        }
    }
};
