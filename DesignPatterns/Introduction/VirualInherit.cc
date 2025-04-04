#include <bits/stdc++.h>
using namespace std;
class base_class {
   public:
    base_class() {
        num = 1;
    }

   public:
    int num;
};

class derived_class : public base_class {
   public:
    derived_class() {
        num = 2;
        // base_class will be default called ahead no matter when and where base_class constructor is called in derived class
    }
};

int main() {
    derived_class BaseWithoutConstructor;
    cout << BaseWithoutConstructor.num;
    return 0;
}