#include <iostream>

template <unsigned N>
struct Factorial {
    //static const long value {long(N)*static_cast<long>(Factorial<N-1>::v::value)};//рекурсивная формула
    enum class v {value = long(N)*static_cast<long>(Factorial<N-1>::v::value)};
};

template<>
struct Factorial<0> {
    enum class v {value = 1};
};

int main() {
    std::cout << static_cast<long>(Factorial<5>::v::value);
    return 0;
}