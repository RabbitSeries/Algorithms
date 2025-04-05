#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename Func, typename... _Args>
class Logger {
    Func func;
    std::string name;
    std::tuple<_Args...> args;  // Store arguments
   public:
    // Constructor
    Logger( Func f, std::string n, _Args&&... ts )
        : func( std::move( f ) ),
          name( std::move( n ) ),
          args( std::forward<_Args>( ts )... ) {
        std::cout << "Logger created: " << name << std::endl;
    }

    // operator(): Invoke the function and handle return type
    auto operator()() {
        std::cout << "Calling: " << name << std::endl;

        if constexpr ( std::is_void_v<std::invoke_result_t<Func, _Args...>> ) {
            // Case: void return type
            std::apply( func, args );
            std::cout << "Finished (void): " << name << std::endl;
        } else {
            // Case: non-void return type
            auto result = std::apply( func, args );
            std::cout << "Finished (returned): " << name << std::endl;
            return result;  // Forward the result
        }
    }
};

// Helper for template deduction (C++17)
template <typename Func, typename... _Args>
Logger( Func, std::string, _Args&&... ) -> Logger<Func, _Args...>;

// Example usage
int main() {
    // Non-void return (int)
    auto int_logger = Logger(
        []( int x, const std::string& s ) -> int {
            std::cout << "Lambda: " << s << ", " << x << std::endl;
            return x * 2;
        },
        "Int Logger",
        42,
        "Hello" );
    int result = int_logger();
    std::cout << "Result: " << result << std::endl;

    // Void return
    auto void_logger = Logger(
        []( const std::string& s ) {
            std::cout << "Void Lambda: " << s << std::endl;
        },
        "Void Logger",
        "World" );
    void_logger();  // No return value
}