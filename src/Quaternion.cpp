#include <cmath>
#include "Quaternion.hpp"
#include "Vector3.hpp"

Quaternion() : x(coords[0]),y(coords[1]),z(coords[2]),w(coords[3]) 
{
	
}

Quaternion(float _x, float _y, float _z, float _w) : x(_x),y(_y),z(_z),w(_w) 
{
}

Quaternion(Vector3 axis, float angle)
{
	float sindiv2 = sin(angle/2);
	float cosdiv2 = cos(angle/2);
	x = axis.x * sindiv2;
	y = axis.y * sindiv2;
	z = axis.z * sindiv2;
	w = cosdiv2;
}