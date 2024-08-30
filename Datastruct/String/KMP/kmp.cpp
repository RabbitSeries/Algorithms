#include "bits/stdc++.h"
using namespace std;
#define maxn 100
int n[maxn];
string text;
string pattern;
/**
 * @brief 00:21:20
 * 
 * @param text 
 * @param cur 
 * @param next 
 * @return int 
 */
int match_recursion(string text, int cur, int next)
{
    if (text[cur] == pattern[next + 1])
    {
        if (next != -1 && pattern[next] == pattern[n[next]])
        {
            return n[next] + 1;
        }
        else
        {
            return next + 1;
        }
    }
    else
    {
        if (next == -1)
        {
            return -1;
        }
        else
        {
            return match_recursion(text, cur, n[next]);
        }
    }
}

int main()
{
    cin >> text >> pattern;
    n[0] = -1;
    for (int i = 1; i < pattern.length(); i++)
    {
        n[i] = match_recursion(pattern, i, n[i - 1]);
    }
    int pos = -1, cnt = 0;
    for (int i = 0; i < text.length();)
    {
        if (text[i] == pattern[pos + 1])
        {
            pos++;
            i++;
        }
        else
        {
            if (pos != -1)
                pos = n[pos];
            else
            {
                i++;
            }
        }
        if (pos == pattern.length()-1)
        {
            cnt++;
            pos = n[pos];
        }
    }
    for_each(n,n+pattern.length(),[](int num){cout << num << " ";});
    cout << endl;

    cout << cnt;
}