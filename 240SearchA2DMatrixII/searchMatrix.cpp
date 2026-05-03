#include <vector> 

using namespace std; 


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size(), cols = matrix[0].size();
        int x = 0, y = cols - 1;
        auto inRange = [&]() {
            return x >= 0 && x < rows && y >= 0 && y < cols;
        };
        while(inRange()) {
            if(matrix[x][y] < target) {
                x++;
            } else if(matrix[x][y] > target) {
                y--;
            } else {
                return true;
            }
        }
        return false;
    }
};