#include <bits/stdc++.h>
using namespace std;
template <class _Tp>
class PointerHandler {
    struct Controller {
        bool valid = true;
        _Tp *ptr = nullptr;
        mutex mtx;
    };
    shared_ptr<Controller> controller;
    // Template helpers
    template <typename...>
    struct all_not_pointer_handler : true_type {};
    template <typename T, typename... Rest>
    struct all_not_pointer_handler<T, Rest...>
        : integral_constant<bool, !is_same<typename decay<T>::type, PointerHandler>::value && all_not_pointer_handler<Rest...>::value> {};

   public:
    template <typename... Args,
              typename enable_if<all_not_pointer_handler<Args...>::value, int>::type = 0>
    PointerHandler( Args &&...args ) : controller( new Controller{ true,
                                                                   new _Tp{ forward<Args>( args )... } },
                                                   []( Controller *ctr ) {
                                                       // dont bind "this" to controller's deletion, as shared_ptr is bind to the PointerHandler when created.
                                                       // But after copy co-tor/co-assign Controller is shared to another PointerHandler.
                                                       // After the copied Handler destructed, shared_ptr triggers deleter which will call the first handler's releaseData() but that's not correct
                                                       if ( ctr->valid ) {
                                                           delete ctr->ptr;
                                                       }
                                                       delete ctr;  // Controller stays untill the last Handler destructed. But _Tp data can be pre-released and thread-safety can be maintained.
                                                   } ) {}
    void releaseData() {
        // mutex lock
        lock_guard ctrLock( controller->mtx );
        if ( controller->valid ) {
            controller->valid = false;
            delete controller->ptr;
            controller->ptr = nullptr;
        }
    }
    optional<_Tp> getData() {
        try {
            lock_guard readMtx( controller->mtx );
            if ( !controller->valid ) {
                throw runtime_error( "Nullptr, Segmentation fault!\n" );
            }
            // Copy Data
            return *controller->ptr;
        } catch ( exception &e ) {
            cerr << e.what();
            return nullopt;
        }
    }
    PointerHandler( const PointerHandler & ) = default;
    PointerHandler &operator=( PointerHandler const & ) = default;
    PointerHandler( PointerHandler && ) noexcept = default;
    PointerHandler &operator=( PointerHandler && ) = default;
    // PointerHandler( const PointerHandler &rhs ) : controller( rhs.controller ) {}
    // PointerHandler &operator=( PointerHandler const &rhs ) {
    //     controller = rhs.controller;
    //     return *this;
    // }
    // PointerHandler( PointerHandler &&rhs ) noexcept : controller( move( rhs.controller ) ) {}
    // PointerHandler &operator=( PointerHandler &&rhs ) noexcept {
    //     controller = move( rhs.controller );
    //     return *this;
    // }
    ~PointerHandler() = default;
};
int main() {
    PointerHandler<pair<int, int>> a{ 1, 2 };
    {
        PointerHandler<pair<int, int>> b( 3, 4 );
        if ( optional<pair<int, int>> v; ( v = b.getData() ).has_value() ) {
            cout << format( "{: >5d} {: >5d}\n", v.value().first, v.value().second );
        }
        a = b;
        b.releaseData();
        PointerHandler<pair<int, int>> c = move( b );
        c.getData();
    }
    auto res = a.getData();
    if ( res.has_value() ) {
        cout << res.value().first << " " << res.value().second << endl;
    }
}