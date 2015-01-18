#include <cmath>
#include <iostream>
#include "ModuleGame.hpp"
#include "Vector3.hpp"

#define MATH_PI 3.14159265358979323846264

float timesTwo(float x)
{
	return 2*x;
}

int main()
{
	Module::ModuleGame g;
	Module::Vector3 vec(0,10,0);
	std::cout << vec.y << std::endl;
	std::cout << vec[1] << std::endl;
	return 0;
}