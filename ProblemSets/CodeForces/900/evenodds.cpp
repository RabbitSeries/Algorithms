#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//10^12
int main()
{
    ll n , k;
    cin >> n >> k;
    // index n numbers first from odds and evens 
    // having 10 nums 
    // indexing from 1 to 5 for 1 , 3, 5 ...
    // having 11 nums
    // indexing from 1 to 6 for 1, 3, 5
    ll half = ceil(1.0*n/2);
    cout << (k<=half?(2*k-1):(2*(k-half)));
    return 0;
}