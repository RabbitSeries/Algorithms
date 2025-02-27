#include <iostream>
#include <cstdio>
using namespace std;
int main()
{
    FILE * f;
    f = fopen("test.txt","r");
    int a,b;
    fscanf(f,"%d%d",&a,&b);
    cout << a << " "<<b;
    return 0;
}