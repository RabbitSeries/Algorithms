#include <iostream>
using namespace std;
int main()
{
    int L,num1,num2;
    cin >> L >> num1 >> num2;
    if (num1 - L >= 0 && num2 - L >= 0)
    {
        cout << "*^_^*";
    }
    else if (num1 >= L && num2 < L)
    {
        cout << "T_T";
    }
    else if (num1 < L && num2 >= L)
    {
        cout << "-_-#";
    }
    else if (num1 < L && num2 < L)
    {
        cout << "-_-";
    }
    return 0;
}