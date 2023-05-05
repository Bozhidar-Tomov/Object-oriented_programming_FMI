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

// Car *dragRace(Car *car1, Car *car2)
// {
//     static const double RACE_DISTANCE = 0.4;
//     Car *winner = nullptr;

//     try
//     {
//         // Use fuel for both cars
//         car1->_fuelTank.use(RACE_DISTANCE);
//         car2->_fuelTank.use(RACE_DISTANCE);

//         // Determine the winner based on weight-to-horsepower ratio
//         winner = (car1->_weight / car1->_engine->getHorsePowers() > car2->_weight / car2->_engine->getHorsePowers()) ? car1 : car2;
//     }
//     catch (insufficient_fuel_exception &exc)
//     { // If one car runs out of fuel, return the other car as the winner
//         // If both cars run out of fuel, return nullptr
//         winner = (exc.getCar() == car1) ? car2 : ((exc.getCar() == car2) ? car1 : nullptr);
//     }
//     catch (std::exception &exc)
//     {
//         std::cout << "Exception occurred: " << exc.what() << '\n'
//                   << "Unsuccessful race.";
//         return nullptr;
//     }
//     catch (...)
//     {
//         std::cout << "Unknown error. Unsuccessful race.";
//         return nullptr;
//     }

//     return winner;
// }

static inline bool isFuelSufficient(FuelTank *tank, void (FuelTank::*useFuel)(double))
{
    static const double RACE_DISTANCE = 0.4;

    try
    {
        (tank->*useFuel)(RACE_DISTANCE);
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
    static bool sufficientFuelCar1 = isFuelSufficient(&(car1->_fuelTank), &FuelTank::use);
    static bool sufficientFuelCar2 = isFuelSufficient(&(car2->_fuelTank), &FuelTank::use);

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
