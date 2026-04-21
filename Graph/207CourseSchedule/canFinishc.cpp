#include <vector>
#include <unordered_set>
#include <deque>
#include <unordered_map>

using namespace std;

/**
 * 广搜，在一个有向图中广搜，看是遍历完所有节点，其实也就是拓扑排序
 */
class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    if(prerequisites.size() == 0) return true;
    unordered_set<int> finish; //能完成的课程，也即是入度可以减少到0的课程
    unordered_map<int, vector<int>> unfinish; //未完成的课程，可能一门课同时有好几门先修课
    int n = prerequisites.size();
    bool res = false;
    for(int i = 0; i < numCourses; i++) finish.insert(i);
    for(auto& course : prerequisites) {
      finish.erase(course[0]); //出去入度不为0的课
      unfinish[course[0]].push_back(course[1]); //这门课的先修要求又多了一门，也即入度又多了一个节点
    }
    if(finish.size() == 0) return false; //一开始没有能完成课，也即没有入度为0的点
    while(true) {
      unordered_set<int> newFinish; //本轮广搜完成了哪些课
      for(auto& [x, y] : unfinish) {
        bool can = true;
        for(int i : y) {
          if(!finish.contains(i)) {
            can = false;
            break;
          }
        }
        if(can) { //如果该未完成的课的先修全部已完成，那么该课也能完成
          newFinish.insert(x);
        }
      }
      for(int i : newFinish) {
        unfinish.erase(i);
        finish.insert(i);
      }
      if(newFinish.size() == 0 && unfinish.size() != 0) { //如果本轮没有能新修的课，并且有未修的课
        res = false;
        break;
      } else if(newFinish.size() == 0 && unfinish.size() == 0) { //全部的课都能修完
        res = true;
        break;
      }
    }
    return res;
  }
};


/**
 * 可以看成有向图的拓扑排序，判断有没有环
 * 这样维护每个节点的入度和出度
 * 每次找到入度为0的节点，把它删掉，并把它指向的节点的入度都减1
 * 是bfs
 */
class Solution {
public:
  bool canFinish(int numsCourses, vector<vector<int>>& prerequisites) {
    //adjacency[i]表示i节点的出箭头指向哪些节点，也就是一个出度表
    vector<vector<int>> adjacency(numsCourses);
    vector<int> inDegrees(numsCourses, 0); // inDegrees[i]表示i节点的入度是几
    for(auto& p : prerequisites) {
      adjacency[p[1]].push_back(p[0]);
      inDegrees[p[0]]++;
    }
    deque<int> que; //入度为0的节点有哪些
    for(int i = 0; i < numsCourses; i++) {
      if(inDegrees[i] == 0) {
        que.push_back(i);
      }
    }
    numsCourses -= que.size(); //此时numsCourse记录着还有几个节点的入度未变为0
    while(!que.empty()) {
      int i = que.front();
      que.pop_front();
      for(int j : adjacency[i]) {
        if(--inDegrees[j] == 0) { //有一个节点的入度变为0
          numsCourses--;
          que.push_back(j);
        }
      }
    }
    return numsCourses == 0;
  }
};

/**
 * 三色标记来判断有没有环，dfs
 * 
 * 0 未被访问过
 * 1 正在访问中，也既是正在递归栈中
 * 2 完全访问完了，没有环存在
 */
class Solution {
public:  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    //adjacency[i]表示i节点的出箭头指向哪些节点，也就是一个出度表
    vector<vector<int>> adjacency(numCourses);
    for(auto& p : prerequisites) {
      adjacency[p[1]].push_back(p[0]);
    }
    vector<int> colors(numCourses, 0); //记录每个节点的颜色状态
    //从x节点出发，一直深度搜索下去，直到搜索完或者找到环，返回从该节点出发是否能找到环
    auto dfs = [&](this auto&& dfs, int x) -> bool {
      colors[x] = 1;
      for(int i : adjacency[x]) { //遍历x的所有出度指向的节点
        // i节点已经是访问中的，又再一次被访问到了，说明存在环
        // i节点没有被访问到，从i节点开始深搜，看有没有环
        if(colors[i] == 1 || (colors[i] == 0 && dfs(i))) {
          return true;
        }
      }
      // 从x节点出发找不到环
      colors[x] = 2;
      return false;
    };
    for(int x = 0; x < numCourses; x++) {
      if(colors[x] == 0 && dfs(x)) { //x节点没有被访问过就搜索它
        return false;
      }
    }
    return true;
  }
};
