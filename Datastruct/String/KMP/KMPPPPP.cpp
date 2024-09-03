#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 100
// input:ababbab output:-1-101-101
int n[maxn];
string model;

/* int find(int pos, int next)
{
    if (model[pos] == model[next + 1])
    {
        return next + 1;
    }
    else
    {
        if (next == -1)
        {
            return -1;
        }
        else
            return find(pos, n[next]);
    }
}
 */

inline int find(int pos, int next)
{
    return model[pos] == model[next + 1] ? next + 1 : next == -1 ? -1
                                                                 : find(pos, n[next]);
}

void kmp()
{
    int next = n[0];
    for (int i = 1; i < model.length();)
    {
        if (model[i] == model[next + 1])
        {
            n[i] = next + 1;
            i++;
            next++;
        }
        else
        {
            if (next == -1)
            {
                n[i] = -1;
                i++;
            }
            else
            {
                next = n[next];
            }
        }
    }
} // abstract

void KMPwithWhile()
{
    int j = -1;
    n[0] = -1;
    for (int i = 1; i < model.length(); i++)
    {
        while (j != -1 && model[i] != model[j + 1])
        {
            j = n[j];
        }
        if (model[i] == model[j + 1])
        {
            n[i] = j + 1;
            j++;
        }
        else
        {
            n[i] = j;
        }
    }
    return;
}
void printNextColumn()
{
    for_each(n, n + model.length(), [](int num)
             { cout << " " << num; });
}

int main()
{
    n[0] = -1;
    cin >> model;
    for (int i = 1; i < model.length(); i++)
    {
        n[i] = find(i, n[i - 1]);
    }
    cout << "Method1:";
    printNextColumn();
    cout << endl;

    cout << "Method2:";
    kmp();
    printNextColumn();
    cout << endl;

    cout << "Method2:";
    KMPwithWhile();
    printNextColumn();
    cout << endl;

    // kmp();
    return 0;
}
