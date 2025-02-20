#include <iostream>
#include <set>
using namespace std;
int main() {
    int numCnt = 0;
    cin >> numCnt;
    set<int, less<>> res;
    for( int i = 0; i < numCnt; i++ ) {
        int curNum;
        cin >> curNum;
        res.insert( curNum );
    }
    for( int num : res ) {
        cout << num << endl;
    }
}