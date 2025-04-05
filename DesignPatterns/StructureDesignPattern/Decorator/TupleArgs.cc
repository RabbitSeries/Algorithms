#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
using namespace std;

template <typename Func, typename... Args>
struct logger {
    Func func;
    string info;
    tuple<typename decay<Args>::type...> args;  // Store decayed copies

    // Constructor: Perfectly forward args
    logger(Func f, string n, Args&&... a)
        : func(move(f)), 
          info(move(n)), 
          args(forward<Args>(a)...) {}  // Correct forwarding

    auto operator()() {
        cout << "Enter: " << info << endl;
        if constexpr (is_void_v<invoke_result_t<Func, Args...>>) {
            apply(func, args);
            cout << "Exit (void): " << info << endl;
        } else {
            auto result = apply(func, args);
            cout << "Exit (returned): " << info << endl;
            return result;
        }
    }
};

// Helper: Deduces Func and Args automatically
template <typename Func, typename... Args>
auto make_logger(Func f, string info, Args&&... args) {
    return logger<Func, Args...>(move(f), move(info), forward<Args>(args)...);
}

int main() {
    int param = 6723;

    // Case 1: void lambda (no return)
    auto logger1 = make_logger(
        [](int p) { cout << "Lambda: " << p << endl; },
        "Hello Decorator 1!",
        param  // lvalue, but forwarded correctly
    );
    logger1();

    // Case 2: int-returning lambda
    auto logger2 = make_logger(
        [](int p) -> int { 
            cout << "Lambda: " << p << endl; 
            return p; 
        },
        "Hello Decorator 2!",
        param  // lvalue, forwarded correctly
    );
    int result = logger2();
    cout << "Result: " << result << endl;

    // Case 3: Multiple args
    auto logger3 = make_logger(
        [](int p1, int p2) { 
            cout << "Params: " << p1 << ", " << p2 << endl; 
        },
        "Decorator 3!",
        6723,  // rvalue (temporary int)
        45     // rvalue (temporary int)
    );
    logger3();
}