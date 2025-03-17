#include <bits/stdc++.h>
using namespace std;

typedef struct minimun_elem
{
    int pos;
    int data;
    minimun_elem(int _p) : pos(_p) {}

    bool operator<(elem e)
    {
        return data < e.data;
    }

} elem;

bool jeted[25000];

bool cmp(elem e1, elem e2) { return e1.data > e2.data; }

priority_queue<elem> last_part;

int main()
{
    int cases;
    cin >> cases;
    while (cases--)
    {
        memset(jeted, 0, 25000);
        int arrayc;
        cin >> arrayc;
        vector<elem> list[arrayc];
        for (int i = 0; i < arrayc; i++)
        {
            int col;
            cin >> col;
            for (int j = 0; j < col; j++)
            {
                elem temp_e(i);
                cin >> temp_e.data;
                list[i].push_back(temp_e);
            }
            sort(list[i].begin(), list[i].end(), cmp);
        }
        vector<elem>::iterator min = list[0].end() - 1;
        for (int i = 1; i < arrayc; i++)
        {
            if (min->data > (list[i].end() - 1)->data)
            {
                min = list[i].end() - 1;
            }
        }
        last_part.push(*min);
        int pos = min->pos;
        for (int i = 1;; /*To-DO*/)
        {
            for (int j = 0; j < arrayc; j++)
            {
                if (j != pos && !jeted[j] && (list[pos].end() - 1 - i)->data > list[j].back().data)
                {
                    elem temp = list[pos].back();
                    list[pos].pop_back();
                    list[pos].push_back(list[j].back());
                    list[j].pop_back();
                    list[pos].push_back(temp);
                    
                }
            }
        }
    }
}