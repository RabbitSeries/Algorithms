#include "boost/lambda/lambda.hpp"
#include <boost/algorithm/algorithm.hpp>
#include <algorithm>
#include "iostream"
using namespace boost::lambda;
using namespace boost::algorithm;
int main() {
    std::vector<int> v{ 1,2,3 };
    std::for_each( v.begin(), v.end(), std::cout << _1 * 2 + 10 << "\n" );
    return 0;
}
