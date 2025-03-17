/**
 * @file Twins.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100;
int num[maxn];
int sum[maxn];
int main()
{
    int pile;
    cin >> pile;
    for (int i = 0; i < pile; i++)
    {
        cin >> num[i];
    }
    sort(num, num + pile);
    memset(sum, 0, sizeof(sum));
    sum[0] = num[0];
    for (int i = 1; i < pile; i++)
    {
        sum[i] = num[i] + sum[i - 1];
    }
    int res = 0, ans = 0;
    for (ans = 1; ans <= pile; ans++)
    {
        res += num[pile - ans];
        if (ans == pile || res > sum[pile - ans - 1])
        {
            break;
        }
    }
    cout << ans;
    return 0;
}