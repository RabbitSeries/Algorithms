#include <bits/stdc++.h>
using namespace std;
#define maxn 2000
typedef struct
{
    int strength;
    int bonus;
} dragon;

dragon level[maxn];

bool cmp(dragon d1, dragon d2)
{
    return d1.strength < d2.strength;
}

int main()
{
    int dragon_n, strength;
    cin >> strength >> dragon_n;

    for (int i = 0; i < dragon_n; i++)
    {
        scanf("%d%d", &level[i].strength, &level[i].bonus);
    }

    sort(level, level + dragon_n, cmp);

    int i;
    for (i = 0; i < dragon_n && strength > level[i].strength; i++)
    {
        strength += level[i].bonus;
    }
    if (i == dragon_n)
    {
        cout << "YES";
        return 0;
    }
    cout << "NO";
    return 0;
}
