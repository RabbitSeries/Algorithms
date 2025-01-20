#include "2045AStar.h"
int main() {
    Solution solution;
    vector<vector<int>> data{ {1,2},{1,3},{2,4},{3,5},{5,4},{4,6} };
    solution.secondMinimum( 6, data, 3, 100 );
    return 0;

}