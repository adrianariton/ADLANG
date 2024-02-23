#include <type_traits>
#include <iostream>

struct A {
    using x = int;
};

struct B {
    using y = int;
};

template<class T>
void f(...) {
    std::cout<<"Structure does not contain x\n";
}

template<class T>
void f(typename T::x*) {
    std::cout<<"Structure contains x\n";
}

int main() {
    f<A>(0);
    f<B>(0);
}