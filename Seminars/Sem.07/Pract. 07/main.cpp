#include <iostream>
#include "MyString.h"

int main()
{
    try
    {
        MyString str = "1234";
        str.resize(16, 'r');

        std::cout << str;
    }
    catch (std::exception &exc)
    {
        std::cout << exc.what();
    }
    catch (...)
    {
        std::cout << "Unknown error.";
    }
}