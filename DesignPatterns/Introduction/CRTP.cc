#include <bits/stdc++.h>
using namespace std;

template <typename Derived>
struct SomeBase {
    void foo() {
        // for ( auto& item : *static_cast<Derived*>( this ) ) {
        auto& item = *static_cast<Derived*>( this );
        item.initialize();
        // }
    }
};

struct Foo1 : SomeBase<Foo1> {
    void initialize() {
        cout << "From Foo 1" << endl;
    }
};

struct Foo2 : SomeBase<Foo2> {
    void initialize() {
        cout << "From Foo 2" << endl;
    }
};

int main() {
    Foo1 f1;
    Foo2 f2;
    f1.foo();
    f2.foo();
}