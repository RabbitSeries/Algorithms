#include <bits/stdc++.h>
using namespace std;
int main(){
    int cases;
    int view[3];//sizeof(view)==20
    cin >> cases;
    int ans=0;
    while(cases--){
        int temp,v=0;
        for(int i = 0 ; i < 3 ; i++){
            cin >> temp;
            if(temp){
                v++;
            }
        }
        if(v>1){
            ans++;
        }
    }
    cout << ans;
    return 0;
}