#pragma once
#include "CarPart.h"
#include <ostream>

class Engine : CarPart
{
	unsigned int _horsePowers = 0;

public:
	Engine(unsigned int ID, const char *manufacturer, const char *description, unsigned short horsePowers);

	friend std::ostream &operator<<(std::ostream &out, const Engine &obj);
};
