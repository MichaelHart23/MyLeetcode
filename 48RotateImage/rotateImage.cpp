#include <vector>

using namespace std;


/**
 * 对于一个n * n的矩阵matrix，对于单个元素matrix[r][l](此处意思是第r行，第l列)
 * 旋转90度意味着什么？
 * 观察其所在的行是如何变化的，以及其所在的列是如何变化的。
 * 发现，第l列的元素会变成第了l行，第r行的元素会变成第n + 1 - r列
 * 进而又发现，旋转就是四轮换
 * matrix[r][l];
 * matrix[l][n + 1 - r];
 * matrix[n + 1 - r][n + 1 - l];
 * matrix[n + 1 - l][r];
 * 如上所示，这四个元素发生了一次轮换，那其实找到所有的轮换就好了
 * 一层壳一层壳的由外向内找，每一层k*k的壳进行k - 1次四轮换
 */

/**
 * 第二种思路：
 * 旋转相当于一次转置 + 一次行翻转
 */
class Solution {
public:
  void rotate(vector<vector<int>>& matrix) {
    int temp, n = matrix.size();
    for(int i = 0; i < n / 2; i++) { //一共有 n / 2 层
      //  i 层是一个（n - 2i）* （n - 2i）的矩阵, j要遍历 n - 2i - 1个数
      for(int j = i; j < n - i - 1; j++) {
        // matrix[i][j];
        // matrix[j][n - 1 - i];
        // matrix[n - 1 - i][n - 1 - j];
        // matrix[n - 1 - j][i];
        // 以上四者就是要轮换的对象
        temp = matrix[j][n - 1 - i];
        matrix[j][n - 1 - i] = matrix[i][j];
        matrix[i][j] = matrix[n - 1 - j][i];
        matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
        matrix[n - 1 - i][n - 1 - j] = temp;
      }
    }
  }
};