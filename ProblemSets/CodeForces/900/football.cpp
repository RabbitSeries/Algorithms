#include <bits/stdc++.h>
using namespace std;
#define maxn 110

int main()
{
    int team1[maxn];//4 bytes
    int team2[maxn];
    string sp;
    getline(cin, sp);
    int len = sp.length();
    memset(team1, 0, sizeof(team1));//按字节赋值
    memset(team2, 0, sizeof(team2));
    team1[0] = (sp[0] == '1') ? 1 : 0;
    team2[0] = (sp[0] == '0') ? 1 : 0;
    for (int i = 1; i < len; i++)
    {
        if (sp[i] == '1')
        {
            team1[i] = team1[i - 1] + 1;
        }
        else
        {
            team2[i] = team2[i - 1] + 1;
        }
        if (team1[i] >= 7 || team2[i] >= 7)
        {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}