#include <stdexcept>

class insufficient_fuel_exception : public std::logic_error
{
public:
    insufficient_fuel_exception(char *msg);
};