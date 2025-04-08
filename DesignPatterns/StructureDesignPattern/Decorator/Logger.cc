#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
using namespace std;
template <typename _Func, typename... _Args>
class logger {
    _Func func;
    string info;  // permenant storage to avoid string_view hanging pointer
    tuple<_Args...> args;

   public:
    logger( _Func _func, string_view _info, _Args&&... _args )
        : func( move( _func ) ),
          info( move( _info ) ),
          args( forward<_Args>( _args )... ) {}
    auto operator()() const  // const allows const logger to be called
    {
        cout << "Enter : " << info << endl;
        if constexpr ( std::is_void_v<std::invoke_result_t<_Func, _Args...>> ) {
            std::apply( func, args );
            std::cout << "Finished (void): " << info << std::endl;
        } else {
            auto result = std::apply( func, args );
            std::cout << "Finished (returned): " << info << std::endl;
            return result;
        }
    }
};

template <typename T, typename... _Args>
void fun( T arg, _Args... args ) {
    cout << "Param: " << arg << endl;
}

template <typename _Func, typename... _Args>
auto make_logger( _Func _func, string_view _info, _Args&&... _args ) {
    return logger<_Func, _Args...>( move( _func ), move( _info ), forward<_Args>( _args )... );
}

int main() {
    int param = 6723;
    logger<function<void( int )>, int>( []( int param ) { cout << "Lambda : param " << param << endl; }, "Hello Decorator 1!", move( param ) )();
    logger( []( int param ) { cout << "Lambda : param " << param << endl; }, "Auto deduced Decorator 2!", move( param ) )();
    param = 45;
    auto r = logger<function<int( int )>, int&>( []( int param ) -> int { cout << "Lambda : param " << param << endl;    return param; }, "Hello Decorator 3!", param )();
    cout << "Decorator 2 returns: " << r << endl;
    auto anyLogger = make_logger( []( int param1, int param2 ) { cout << "Param 1: " << param1 << " Param 2: " << param2 << endl; }, "Decorator 4!", param, 45 );
    less<>{};
    anyLogger();
}