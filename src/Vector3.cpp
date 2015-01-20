#include "Vector3.hpp"

using Module::Vector3;

Vector3::Vector3() : x(0),y(0),z(0) {}

Vector3::Vector3(float _x, float _y, float _z) : x(_x),y(_y),z(_z) {}

Vector3 Vector3::operator*(float scalar) const // scalar multiplication
{
	return Vector3(	x * scalar,
					y * scalar,
					z * scalar);
}
	
Vector3 Vector3::operator*(const Vector3& other) const // component-wise multiplication
{
	return Vector3( x * other.x,
					y * other.y,
					z * other.z);
}

Vector3& Vector3::operator*=(float scalar) // scalar multiplication assignment
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return (*this);
}

Vector3& Vector3::operator*=(const Vector3& other) // component-wise multiplication assignment
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return (*this);
}

Vector3 Vector3::operator+(const Vector3& other) const // vector addition
{
	return Vector3(	x + other.x,
					y + other.y,
					z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other) // addition assignment
{
	x += other.x;
	y += other.y;
	z += other.z;
	return (*this);
}

Vector3 Vector3::operator-() const // negation
{
	return Vector3(-x,-y,-z);
}

Vector3 Vector3::operator-(const Vector3& other) const // vector subtraction
{
	return Vector3(	x - other.x,
					y - other.y,
					z - other.z);
}

Vector3& Vector3::operator-=(const Vector3& other) // addition assignment
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return (*this);
}

Vector3 Vector3::cross(const Vector3& other) const // vector cross product
{
	return Vector3(	y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
}

float Vector3::dot(const Vector3& other) const // vector dot product
{
	return x * other.x + y * other.y + z * other.z;
}