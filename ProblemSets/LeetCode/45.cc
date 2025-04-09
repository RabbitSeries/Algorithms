#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int trap( vector<int>& height ) {
        vector<int> left( height.size() ), right( height.size() );
        partial_sum( height.begin(), height.end(), left.begin(), ranges::max );
        partial_sum( height.rbegin(), height.rend(), right.rbegin(), ranges::max );
        int total = 0;
        for ( size_t i = 0; i < height.size(); i++ ) {
            total += min( left[i], right[i] ) - height[i];
        }
        return total;
    }
};
int main() {
    vector<int> test{ 4, 2, 0, 3, 2, 5 };
    cout << Solution().trap( test );
}