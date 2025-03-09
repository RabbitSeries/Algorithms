#include <bits/stdc++.h>

#include <future>
#include <iostream>
#include <thread>
class globalClass : std::future<int> {
   public:
    static int SingletonArgc;
    static char** SingletonArgv;

    globalClass( int argc, char* argv[] ) {
        SingletonArgc = argc;
        SingletonArgv = argv;
        instance();
    };
    globalClass( globalClass const& ) = delete;
    globalClass( globalClass&& ) = delete;
    globalClass& operator=( globalClass const& ) = delete;
    globalClass& operator=( globalClass&& ) = delete;

    static globalClass* instance() {
        static globalClass* singleton = new globalClass();
        return singleton;
    }

    static int run() {
        while ( 1 ) {
            ;
        }
        return 0;
    }

    static std::thread::id currentThread() {
        return std::this_thread::get_id();
    }

    static int exec() {
        std::cout << "Entring evnetLoop";
        std::cout.flush();
        instance()->wait();
        return instance()->get();
    }

   protected:
    globalClass() : future<int>( std::async( std::launch::deferred, run ) ) {
        std::cout << "Creating thread" << std::endl;
    }
};

int globalClass::SingletonArgc = 0;
char** globalClass::SingletonArgv = nullptr;

int main( int argc, char* argv[] ) {
    using namespace std;
    globalClass app( argc, argv );
    cout << "Current at:" << globalClass::currentThread() << endl;
    return globalClass::instance()->exec();
}