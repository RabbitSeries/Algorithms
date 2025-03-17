#include <bits/stdc++.h>
using namespace std;
int main(){
    int lc;
    string line;
    cin >> lc;
    while (lc--){
        cin >> line;
        int LineSize = line.size();
        if(LineSize >  10){ // strictly more than 10 words
            cout << line[0];
            cout << LineSize-2;
            cout << line[LineSize-1];
            cout << endl;
        }
        else{
            cout << line << endl;
        }
    }
    return 0;
}