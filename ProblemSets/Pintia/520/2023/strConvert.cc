// produce c char
// const char* "asdasd",{'0'},string.c_str();
#include <cstdio>
#include <iostream>

#define elem int;
#ifdef ELEM_INT
typedef elem int;
#elif ELEM_CHAR
typedef elem char;
#endif

using namespace std;
char SingleAssign[10] = { '1', '2', '3', '4' };
char *str = SingleAssign;  // Legal
// char str[10] = SingleAssign; //Illegal
// char str[10] = SingleAssign; //Illegal
char GroupAssign[] = "1234";
char str2[] = { '1', '2', '3', '4' };
char str3[] = { '1', '2', '3', '4' };
// char str4[10] = str2;
char str5[10] = "1234";
char str6[10] = { '1', '2', '3', '4' };
char *str7 = str2;
char *str8 = "1234";
const char *str9 = "1234";
void fun() {
    str8 = "3456";
    str9 = "3456";
}
// Produce string
string str3( str2 );
string str3( "sadas" );
// string str3( string str4 );
int main(){
    
}