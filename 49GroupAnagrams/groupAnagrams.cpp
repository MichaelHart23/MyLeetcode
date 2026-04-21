#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string>& strs) {
  string s;
  s.assign(26, '0');
  unordered_map<string, vector<string>> map;
  for(string &str : strs) {
    string key(s);
    for(char c : str) {
      key[c - 'a']++;
    }
    map[key].push_back(str);
  }
  vector<vector<string>> res;
  res.resize(map.size());
  for(auto &it : map) {
    res.emplace_back(std::move(it.second));
  }
  return res;
}

int main() {} 