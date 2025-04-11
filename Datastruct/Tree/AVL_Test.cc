#include "AVL.hpp"
#include "AVL_Iterative.hpp"
using namespace std;
vector<int> TestCase( 1000000 );
void Case1() {
    auto Time1 = chrono::high_resolution_clock::now();
    AVL_Ietrative::node<int, less<>>* root1{ nullptr };
    for ( int val : TestCase ) {
        using namespace AVL_Ietrative;
        root1 = insert( root1, val );
    }
    cout << root1->height << endl;
    for ( int val : TestCase ) {
        using namespace AVL_Ietrative;
        // Solution1::insert( root1, val );
        root1 = delNode( root1, val );
    }
    auto Time2 = chrono::high_resolution_clock::now();
    cout << "Recursive: " << chrono::duration_cast<chrono::milliseconds>( Time2 - Time1 ).count() << endl;
}
void Case2() {
    auto Time1 = chrono::high_resolution_clock::now();
    AVL::node<int, less<>>* root2{ nullptr };
    for ( int val : TestCase ) {
        using namespace AVL;
        // Solution1::insert( root1, val );
        root2 = insert( root2, val );
    }
    cout << root2->height << endl;
    for ( int val : TestCase ) {
        using namespace AVL;
        // Solution1::insert( root1, val );
        root2 = delNode( root2, val );
    }
    auto Time2 = chrono::high_resolution_clock::now();
    cout << "Iterative: " << chrono::duration_cast<chrono::milliseconds>( Time2 - Time1 ).count() << endl;
}
int main() {
    stack<int, vector<int>> stk;
    iota( begin( TestCase ), end( TestCase ), 0 );
    Case1();
    Case2();
    // Actually AVL stack space complexity is logN, which means over 65536 nodes only require 16 blocks stack context.
    // OS process stack maintenance cost is significantly low.
    // So Iterative's stack STL's cost won't worth it.
}