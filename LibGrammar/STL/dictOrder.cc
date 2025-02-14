#include <string>
#include <set>
#include <iostream>
using namespace std;
int main() {
    set<string, greater<>> cmpList;
    cmpList.insert( "001" );
    cmpList.insert( "001" );
    cmpList.insert( "001" );
    cmpList.insert( "221" );
    cmpList.insert( "921" );
    cmpList.insert( "21" );
    cmpList.insert( "1" );
    for( auto key : cmpList ) {
        cout << key << endl;
    }
    return 0;
}