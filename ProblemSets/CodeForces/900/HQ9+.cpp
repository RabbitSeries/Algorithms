#include <bits/stdc++.h>
using namespace std;
int main()
{
    string in_str;
    getline(cin,in_str);
    for (int i = 0 ; i < in_str.size() ; i++){
        if (in_str[i] == 'H' ||in_str[i] == 'Q' ||in_str[i] == '9'){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO" ;
    return 0;
}