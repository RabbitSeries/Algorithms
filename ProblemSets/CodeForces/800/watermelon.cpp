#include <bits/stdc++.h>
using namespace std;
int main()
{
    int scale;
    scanf("%d",&scale);
    for (int i = 1 ; i <= scale/2 ; i ++){
        if ( i %2 == 0 && (scale - i ) % 2 == 0){
            printf("YES");
            return 0;
        }
    }
    printf("NO");
    return 0;
}