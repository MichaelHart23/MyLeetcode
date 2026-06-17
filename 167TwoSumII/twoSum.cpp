#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int start = 0;
        int end = numbers.size() - 1;
        while (true) {
            while (numbers[start] + numbers[end] > target) {
                end--;
            }
            if (numbers[start] + numbers[end] == target) {
                return {start + 1, end + 1};
            }
            start++;
        }
    }
};