#pragma once
#include <ostream>
#include "CarPart.h"

class CarBattery : CarPart
{
	unsigned int _capacity = 0;
	char *_batteryID = nullptr;

public:
	CarBattery(unsigned int ID, const char *manufacturer, const char *description,
			   unsigned int capacity, char *batteryID);
	CarBattery(const CarBattery &other);
	CarBattery &operator=(const CarBattery &other);
	~CarBattery();

	friend std::ostream &operator<<(std::ostream &out, const CarBattery &obj);

private:
	void copyFrom(const CarBattery &other);
	void copyBatteryID(const char *batteryID);
	void free();
};
