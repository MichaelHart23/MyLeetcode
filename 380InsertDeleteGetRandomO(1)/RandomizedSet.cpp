#include <unordered_map>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

/**
 * 数组加强哈希表，插入删除getRandom都是O(1)的时间复杂度
 * 删除操作采末尾元素替换的方法进行删除，也是O(1)
 */
class RandomizedSet {
    vector<int> vals;
    unordered_map<int, int> mp;

public:
    RandomizedSet() {
    }

    bool insert(int val) {
        auto it = mp.find(val);
        if (it != mp.end()) {
            return false;
        }
        vals.push_back(val);
        mp.insert({val, vals.size() - 1});
        return true;
    }

    bool remove(int val) {
        auto it = mp.find(val);
        if (it == mp.end()) {
            return false;
        }
        int index = it->second;
        int last = vals.back();
        vals[index] = last;
        mp[last] = index;
        mp.erase(it);
        vals.pop_back();
        return true;
    }

    int getRandom() {
        int index = rand() % vals.size();
        return vals[index];
    }
};
