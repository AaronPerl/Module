#include "Vector3.hpp"
#include <iostream>

using Module::Vector3;

Vector3::Vector3() : coords(),x(coords[0]),y(coords[1]),z(coords[2]) {}

Vector3::Vector3(float _x, float _y, float _z) : x(coords[0]),y(coords[1]),z(coords[2])
{
	coords[0] = _x;
	coords[1] = _y;
	coords[2] = _z;
}

Vector3 Module::Vector3::operator*(const Vector3& other) // component-wise multiplication
{
	return Vector3( x * other.x,
					y * other.y,
					z * other.z);
}

Vector3 Module::Vector3::operator+(const Vector3& other) // vector addition
{
	return Vector3(	x + other.x,
					y + other.y,
					z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other) // addition assignment
{
	coords[0] += other.x;
	coords[1] += other.y;
	coords[2] += other.z;
	return (*this);
}

Vector3 Vector3::operator-() // negation
{
	return Vector3(-x,-y,-z);
}

Vector3 Vector3::operator-(const Vector3& other) // vector subtraction
{
	return Vector3(	x - other.x,
					y - other.y,
					z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other) // addition assignment
{
	coords[0] -= other.x;
	coords[1] -= other.y;
	coords[2] -= other.z;
	return (*this);
}


const float& Vector3::operator[](int index) // index
{
	return coords[index];
}

const float* Vector3::getCoords()
{
	return coords;
}

Vector3 Vector3::cross(const Vector3& other) // vector cross product
{
	return Vector3(	y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
}

float Vector3::dot(const Vector3& other) // vector dot product
{
	return x * other.x + y * other.y + z * other.z;
}