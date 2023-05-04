#include <iostream>
using namespace std;

class Base
{
public:
    int x;
    Base(int x) : x(x) {}
    friend ostream &operator<<(ostream &os, const Base &b);
};

ostream &operator<<(ostream &os, const Base &b)
{
    os << "Base: " << b.x;
    return os;
}

class Derived : public Base
{
public:
    int y;
    Derived(int x, int y) : Base(x), y(y) {}
    friend ostream &operator<<(ostream &os, const Derived &d);
};

ostream &operator<<(ostream &os, const Derived &d)
{
    // call parent class's operator<<
    operator<<(os, (const Base &)d);
    os << ", Derived: " << d.y;
    return os;
}

int main()
{
    Derived d(1, 2);
    cout << d << endl; // prints "Base: 1, Derived: 2"
}