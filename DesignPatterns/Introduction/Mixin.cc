#include <bits/stdc++.h>

using namespace std;
template <typename T>
struct Mixin : T {
};

namespace WRAPED_FUNCTIONS {
void myFun( int num ) {
    cout << num << endl;
}
}  // namespace WRAPED_FUNCTIONS

int main() {
    cout << typeid( "Hello"s ).name() << endl;
    using WRAPED_FUNCTIONS::myFun;
    myFun( 19 );
}