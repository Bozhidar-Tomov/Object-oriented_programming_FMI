#pragma once
#include "FuelTank.h"
#include "Engine.h"
#include "Tire.h"
#include "CarBattery.h"

class Car
{
    Engine *engine = nullptr;
    Tire *tires[4];
    CarBattery *carBattery = nullptr;
    FuelTank fuelTank;

    unsigned distanceTraveled = 0;
    unsigned weight = 0;

public:
    Car(
        unsigned int, const char *, const char *,
        unsigned short,
        unsigned short, unsigned short, unsigned short,
        unsigned int, char *,
        double,

        unsigned = 0,
        unsigned = 0);

    const FuelTank &getFuelTank() const;
    void drive(double);

    friend Car *dragRace(Car *car1, Car *car2);
};
