#pragma once
class FuelTank
{
	double _capacity = 0;
	double _currentLevel = 0;

public:
	FuelTank(double);

	void use(double amount);
	void fill(double amount);
};
