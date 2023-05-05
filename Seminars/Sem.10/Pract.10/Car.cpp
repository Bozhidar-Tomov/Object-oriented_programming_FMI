#include <iostream>
#include "Car.h"
#include "insufficient_fuel_exception.h"

Car::Car(
    unsigned int ID, const char *manufacturer, const char *description,
    unsigned short horsePowers,
    unsigned short width, unsigned short profile, unsigned short diameter,
    unsigned int capacity, char *batteryID,
    double fuelTankCapacity,

    unsigned distanceTraveled,
    unsigned weight) : fuelTank(fuelTankCapacity), distanceTraveled(distanceTraveled), weight(weight)
{
    engine = new Engine(ID, manufacturer, description, horsePowers);

    for (int i = 0; i < 4; ++i)
        tires[i] = new Tire(ID, manufacturer, description, width, profile, diameter);

    carBattery = new CarBattery(ID, manufacturer, description, capacity, batteryID);
}

const FuelTank &Car::getFuelTank() const
{
    return fuelTank;
}

void Car::drive(double km)
{
    try
    {
        fuelTank.use(km);
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

    distanceTraveled += km;
}

Car *dragRace(Car *car1, Car *car2)
{
    static const double RACE_DISTANCE = 0.4;
    Car *winner = nullptr;
    bool insufficientFuelCar1 = false;
    bool insufficientFuelCar2 = false;

    try
    {
        car1->fuelTank.use(RACE_DISTANCE);
    }
    catch (insufficient_fuel_exception &exc)
    {
        insufficientFuelCar1 = true;
    }
    catch (...)
    {
        std::cout << "Unknown error. Unsuccessful race";
        return nullptr;
    }

    try
    {
        car2->fuelTank.use(RACE_DISTANCE);
    }
    catch (insufficient_fuel_exception &exc)
    {
        insufficientFuelCar2 = true;
    }
    catch (...)
    {
        std::cout << "Unknown error. Unsuccessful race";
        return nullptr;
    }

    if (insufficientFuelCar1 && insufficientFuelCar2)
    {
        return nullptr;
    }

    if (insufficientFuelCar1 && !insufficientFuelCar2)
    {
        return car2;
    }

    if (!insufficientFuelCar1 && insufficientFuelCar2)
    {
        return car1;
    }

    if (car1->weight / car1->engine->getHorsePowers() > car1->weight / car1->engine->getHorsePowers())
        return car1;
    else
        return car2;
}