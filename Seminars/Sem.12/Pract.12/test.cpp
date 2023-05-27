#include <iostream>
using namespace std;

class Base
{
public:
    void (Base::*callback)(int);
    void callCallback(int x)
    {
        if (callback)
            (this->*callback)(x);
    }
};

class DerivedA : public Base
{
public:
    DerivedA() { callback = (void(Base::*)(int)) & DerivedA::f; }
    void f() { cout << "DerivedA::f(int x), x = " << endl; }
};

class DerivedB : public Base
{
public:
    DerivedB() { callback = (void(Base::*)(int)) & DerivedB::f; }
    void f(int x) { cout << "DerivedB::f(int x), x = " << x << endl; }
};

int main()
{
    DerivedA a;
    a.callCallback(1); // prints "DerivedA::f(int x), x = 1"

    DerivedB b;
    b.callCallback(2); // prints "DerivedB::f(int x), x = 2"

    return 0;
}