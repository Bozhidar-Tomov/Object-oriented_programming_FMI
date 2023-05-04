#include "Engine.h"

Engine::Engine(unsigned int ID, const char *manufacturer, const char *description, unsigned short horsePowers) : CarPart(ID, manufacturer, description)
{
	_horsePowers = horsePowers;
}

std::ostream &operator<<(std::ostream &out, const Engine &obj)
{
	return out << (const CarPart &)obj << " - "
			   << obj._horsePowers << "hp";
}
