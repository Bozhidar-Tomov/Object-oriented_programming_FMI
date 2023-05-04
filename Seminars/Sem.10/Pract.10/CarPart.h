#pragma once
#include <ostream>

class CarPart
{
	unsigned int _ID = 0;
	char *_manufacturer = nullptr;
	char *_description = nullptr;

public:
	CarPart(unsigned int ID, const char *manufacturer, const char *description);
	CarPart(const CarPart &other);
	CarPart &operator=(const CarPart &other);

public:
	friend std::ostream &operator<<(std::ostream &out, const CarPart &obj);

private:
	void copyFrom(const CarPart &other);
	void copyManufacturer(const char *data);
	void copyDescription(const char *data);
	void free();
};
