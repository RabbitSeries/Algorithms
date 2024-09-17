#include <iostream>

int main() {
#if defined(__GNUC__) || defined(__GNUG__)
    std::cout << "Compiler: GCC\n";
    std::cout << "Version: " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__ << "\n";
#elif defined(_MSC_VER)
    std::cout << "Compiler: MSVC\n";
    std::cout << "Version: " << _MSC_VER << "\n";
#elif defined(__clang__)
    std::cout << "Compiler: Clang\n";
    std::cout << "Version: " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__ << "\n";
#else
    std::cout << "Unknown compiler\n";
#endif

#if defined(_WIN32)
    std::cout << "Platform API: Windows 32 bit";
#elif defined(__linux__)
    std::cout << "Platform: Linux\n";
#elif defined(__APPLE__)
    std::cout << "Platform: macOS\n";
#else
    std::cout << "Unknown platform\n";
#endif
    std::cout << "cpp version: " << __cplusplus;
    return 0;
}
