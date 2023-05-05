#include <iostream>
#include "Car.h"
#include "insufficient_fuel_exception.h"

Car::Car(Engine *engine,
         Tire *tires[4],
         CarBattery *carBattery,
         double fuelTankCapacity,
         unsigned int distanceTraveled,
         unsigned int weight) : _engine(engine), _carBattery(carBattery),
                                _fuelTank(fuelTankCapacity),
                                _distanceTraveled(distanceTraveled),
                                _weight(weight)
{
    for (unsigned short i = 0; i < 4; ++i)
        _tires[i] = tires[i];
}

const FuelTank &Car::getFuelTank() const
{
    return _fuelTank;
}

void Car::drive(double km)
{
    try
    {
        _fuelTank.use(km);
    }
    catch (insufficient_fuel_exception &err)
    {
        std::cout << err.what() << "\n"
                  << "Unsuccessful drive.";
    }
    catch (std::exception exc)
    {
        std::cout << "Exception occurred: " << exc.what() << "\n"
                  << "Unsuccessful drive.";
    }
    catch (...)
    {
        std::cout << "Unknown error. Unsuccessful drive.";
    }

    _distanceTraveled += km;
}

/*
Reasons I used a higher order function here, although it is not necessary:
1) To practice this concept
2) Not to repeat the code, handling errors (D.R.Y.)
*/

// We take a pointer to a Car method and Car object on which to call the method
static inline bool isFuelSufficient(Car *car, void (Car::*drive)(double))
{
    static const double RACE_DISTANCE = 0.4;

    try
    {
        // car is pointer, so we have to dereference it, *drive is function pointer, so we have to dereference *drive aas well
        // That is why we have   car->*drive   or   (*car).*drive   syntax.
        //                      ‾‾‾‾‾‾‾‾‾‾‾‾‾      ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
        (car->*drive)(RACE_DISTANCE);
    }
    catch (insufficient_fuel_exception &exc)
    {
        return false;
    }
    catch (std::exception &exc)
    {
        std::cout << "Exception occurred: " << exc.what() << '\n'
                  << "Unsuccessful race.";
        return false;
    }
    catch (...)
    {
        std::cout << "Unknown error. Unsuccessful race.";
        return false;
    }

    return true;
}

Car *dragRace(Car *car1, Car *car2)
{
    // Passing the pointer to Car obj and the address of Car::drive function
    static bool sufficientFuelCar1 = isFuelSufficient(car1, &Car::drive);
    static bool sufficientFuelCar2 = isFuelSufficient(car2, &Car::drive);

    if (sufficientFuelCar1 && sufficientFuelCar2)
    {
        return (car1->_weight / car1->_engine->getHorsePowers() > car2->_weight / car2->_engine->getHorsePowers()) ? car1 : car2;
    }
    if (sufficientFuelCar1 && !sufficientFuelCar2)
    {
        return car1;
    }
    if (!sufficientFuelCar1 && sufficientFuelCar2)
    {
        return car2;
    }

    return nullptr;
}

std::ostream &operator<<(std::ostream &out, const Car &obj)
{
    return out << "Engine: " << *(obj._engine) << '\n'
               << "Tires: " << '\n'
               << '\t' << "Tire (1): " << *(obj._tires[0]) << '\n'
               << '\t' << "Tire (2): " << *(obj._tires[1]) << '\n'
               << '\t' << "Tire (3): " << *(obj._tires[2]) << '\n'
               << '\t' << "Tire (4): " << *(obj._tires[3]) << '\n'
               << "Car battery: " << *(obj._carBattery) << '\n'
               << "Distance traveled: " << obj._distanceTraveled << " km." << '\n'
               << "Weight: " << obj._weight << " kg." << '\n';
}
