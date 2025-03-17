#include <bits/stdc++.h>
using namespace std;
#define maxn 5001
int n;
string strA;
string strB;

pair<int, int> zone;
bool available;
void opt(string &a, string &b, int pos);
bool lrfind(string a, char c, int pos);
void lrreverse(string &r, pair<int, int> pos);

void opt(string &a, string &b, int pos)
{
    if (pos == a.size() - 1)
    {
        available = true;
        return;
    }
    if (a[pos] == b[pos])
    {
        opt(a, b, pos + 1);
        return;
    }
    else if (a[pos] != b[pos])
    {
        if (lrfind(a, a[pos], pos))
        {
            lrreverse(a, zone);
            opt(a, b, zone.first + 1);
            return;
        }
        else if (lrfind(b, b[pos], pos))
        {
            lrreverse(b, zone);
            opt(a, b, zone.first + 1);
            return;
        }
        else
        {
            available = false;
            return;
        }
    }
}

bool lrfind(string a, char c, int pos)
{
    c = (c == '0') ? '1' : '0';
    for (int i = pos - 1; i >= 0; i--)
    {
        if (a[i] == c)
        {
            zone.first = i;
            for (int j = pos + 1; j < a.size(); j++)
            {
                if (a[j] == c)
                {
                    zone.second = j;
                    return true;
                }
            }
        }
        break;
    }
    return false;
}

void lrreverse(string &r, pair<int, int> pos)
{
    string c = (r[pos.first] == '0') ? "0" : "1";
    for (int i = pos.first + 1; i < pos.second; i++)
    {
        r.replace(r.begin() + i, r.begin() + i + 1, c);
    }
}

void generate(string s,int len)
{
    string t1 = s, t2 = s;
    t1 += "0";
    string t3 = "0" + t1 + "1";

    generate(t1,len+1);
    t2 += "1";
    string t4 = "0" + t2 + "1";
    generate(t2,len+1);
}

bool judge(string s1, string s2)
{
    int j;
    for (j = 1; j < strA.size(); j++)
    {
        if (strA[j - 1] == '0' && strA[j] == '1' && strB[j - 1] == '0' && strB[j] == '1')
        {

            break;
        }
    }
    if (j < strA.size())
    {
        cout << "YES\n";
    }
}

int main()
{
    cin >> n;
    getchar();
    for (int i = 0; i < n; i++)
    {
        getline(cin, strA);
        getline(cin, strB);
        /*         available = false;
                opt(strA, strB, 1);

                if (available)
                {
                    cout << "YES" << endl;
                }
                else
                {
                    cout << "NO" << endl;
                } */
    }
    return 0;
}