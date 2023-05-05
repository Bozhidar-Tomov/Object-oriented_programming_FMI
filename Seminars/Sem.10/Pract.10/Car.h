#pragma once
#include <ostream>
#include "FuelTank.h"
#include "Engine.h"
#include "Tire.h"
#include "CarBattery.h"

class Car
{
    FuelTank _fuelTank;
    Engine *_engine = nullptr;
    Tire *_tires[4];
    CarBattery *_carBattery = nullptr;

    unsigned _distanceTraveled = 0;
    unsigned _weight = 0;

public:
    Car(Engine *, Tire *[4], CarBattery *, double, unsigned int, unsigned int);

    const FuelTank &getFuelTank() const;
    void drive(double);

    friend Car *dragRace(Car *, Car *);
    friend std::ostream &operator<<(std::ostream &, const Car &);
};
