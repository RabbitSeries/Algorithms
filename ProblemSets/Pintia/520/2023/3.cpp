#include <iostream>
#include <vector>
using namespace std;
int main() {
    int num;
    cin >> num;
    vector<int> love( num );
    for ( int i = 0; i < num - 1; i++ ) {
        cin >> love[i];
        if ( love[i] % 2 ) {
            cout << "Love!" << endl;
        } else {
            cout << "!Love" << endl;
        }
    }
    cin >> love[num - 1];
    if ( love[num - 1] % 2 ) {
        cout << "Love!";
    } else {
        cout << "!Love";
    }
    return 0;
}