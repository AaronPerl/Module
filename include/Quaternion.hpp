#ifndef __MODULE__QUATERNION_HPP__
#define __MODULE__QUATERNION_HPP__

#include "Vector3.hpp"

namespace Module {

class Quaternion {
private:
	float coords[4];
	float& x;
	float& y;
	float& z;
	float& w;
public:
	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(Vector3 axis, float angle);
	
	/*Vector3 operator*(const Vector3& other) // component-wise multiplication
	{
		return Vector3( x * other.x,
						y * other.y,
						z * other.z);
	}
	
	Vector3 operator+(const Vector3& other) // vector addition
	{
		return Vector3(	x + other.x,
						y + other.y,
						z + other.z);
	}
	
	Vector3 operator-() // negation
	{
		return Vector3(-x,-y,-z);
	}
	
	Vector3 cross(const Vector3& other) // vector cross product
	{
		return Vector3(	y * other.z - z * other.y,
						z * other.x - x * other.z,
						x * other.y - y * other.x);
	}
	
	float dot(const Vector3& other) // vector dot product
	{
		return x * other.x + y * other.y + z * other.z;
	}
	
	Vector3& operator+=(const Vector3& other) // addition assignment
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return (*this);
	}*/
	
	
};

}

#endif