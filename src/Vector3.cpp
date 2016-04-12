#include "Vector3.hpp"
#include "Quaternion.hpp"

using Module::Vector3;

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3::Vector3(float _x, float _y, float _z) : x(_x),y(_y),z(_z) {}

// Scalar multiplication
Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(	x * scalar,
					y * scalar,
					z * scalar);
}

// Component-wise multiplication
Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3( x * other.x,
					y * other.y,
					z * other.z);
}

// Scalar multiplication assignment
Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return (*this);
}

// Component-wise multiplication assignment
Vector3& Vector3::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return (*this);
}

// Vector addition
Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(	x + other.x,
					y + other.y,
					z + other.z);
}

// Addition assignment
Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return (*this);
}

// Negation
Vector3 Vector3::operator-() const
{
	return Vector3(-x,-y,-z);
}

// Vector subtraction
Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(	x - other.x,
					y - other.y,
					z - other.z);
}

// Addition assignment
Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return (*this);
}

// Rotate a Vector3
Vector3 Vector3::rotate(const Quaternion& other) const
{
	Quaternion self(x,y,z,0);
	Quaternion result = (other * self) * other.inverse();
	return Vector3(result.getX(),result.getY(),result.getZ());
}

// Vector cross product
Vector3 Vector3::cross(const Vector3& other) const
{
	return Vector3(	y * other.z - z * other.y,
					z * other.x - x * other.z,
					x * other.y - y * other.x);
}

// Vector dot product
float Vector3::dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}