#pragma once
#include "CarPart.h"
#include <ostream>

class Tire : CarPart
{
	unsigned short _width = 0;
	unsigned short _profile = 0;
	unsigned short _diameter = 0;

public:
	Tire(unsigned int, const char *, const char *, unsigned short, unsigned short, unsigned short);

	friend inline std::ostream &operator<<(std::ostream &out, const Tire &obj);

private:
	static inline bool isWidthValid(unsigned int width);
	static inline bool isProfileValid(unsigned int profile);
	static inline bool isDiameterValid(unsigned int diameter);
};
