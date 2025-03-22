#include <bits/stdc++.h>
using namespace std;
// struct myInt {
//     int val;
//     friend bool operator==( const myInt& m1, const myInt& m2 ) { return m1.val == m2.val; }
// };
// template <>
// struct std::hash<myInt> {
//     int operator()( const myInt& val ) const {
//         return val.val;
//     }
// };
int main() {
    int hashArray[10000]{ 0 };
    default_random_engine e;
    // unordered_map<myInt, int> hashMap;
    unordered_map<int, int> hashMap;
    uniform_int_distribution udf( 0, 9999 );
    for ( int i = 0; i < 100000000; i++ ) {
        int curR = udf( e );
        hashArray[curR]++;
        // hashMap[myInt{ curR }]++;
        hashMap[curR]++;
    }
    auto now = chrono::high_resolution_clock::now();
    int arrayStatistic = 0;
    for ( int i = 0; i < 100000000; i++ ) {
        int curR = udf( e );
        if ( hashArray[curR] > 0 ) arrayStatistic++;
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "Array query cost: " << chrono::duration_cast<chrono::microseconds>( end - now ).count() / 1000 << " ms." << endl;

    now = chrono::high_resolution_clock::now();
    int hashMapStatistic = 0;
    for ( int i = 0; i < 100000000; i++ ) {
        int curR = udf( e );
        // if ( hashMap.count( myInt{ curR } ) ) hashMapStatistic++;
        if ( hashMap.contains( curR ) ) hashMapStatistic++;
    }
    end = chrono::high_resolution_clock::now();
    cout << "Hashmap query cost: " << chrono::duration_cast<chrono::microseconds>( end - now ).count() / 1000 << " ms." << endl;
}