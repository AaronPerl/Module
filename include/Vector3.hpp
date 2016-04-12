#ifndef __MODULE__VECTOR3_HPP__
#define __MODULE__VECTOR3_HPP__

#include <iostream>

namespace Module {

class Quaternion;

// A simple 3D Vector class. Not optimized
class Vector3
{
	private:
		float x,y,z;
	public:
		
		Vector3();										// default constructor
		Vector3(float x, float y, float z);				// constructor with arguments
		
		Vector3 operator*(float scalar) const;			// scalar multiplication
		Vector3 operator*(const Vector3& other) const;	// component-wise multiplication
		Vector3& operator*=(float scalar);				// scalar multiplication assignment
		Vector3& operator*=(const Vector3& other);		// component-wise multiplication assignment
		Vector3 operator+(const Vector3& other) const;	// vector addition
		Vector3& operator+=(const Vector3& other);		// addition assignment
		Vector3 operator-() const;						// negation
		Vector3 operator-(const Vector3& other) const;	// vector subtraction
		Vector3& operator-=(const Vector3& other);		// subtraction assignment
		
		Vector3 rotate(const Quaternion& other) const;	// quaternion rotation
		
		float getX() const;								// A getter for x
		float getY() const;								// A getter for y
		float getZ() const;								// A getter for z
		
		Vector3 cross(const Vector3& other) const; 		// vector cross product	
		float dot(const Vector3& other) const; 			// vector dot product		
};

/** Gets the x-coordinate of this Vector3
 * @return The x-coordinate of this Vector3
*/
inline float Vector3::getX() const
{
	return x;
}

/** Gets the y-coordinate of this Vector3
 * @return The y-coordinate of this Vector3
*/
inline float Vector3::getY() const
{
	return y;
}

/** Gets the z-coordinate of this Vector3
 * @return The z-coordinate of this Vector3
*/
inline float Vector3::getZ() const
{
	return z;
}
/*
// Ostream insertion operator
std::ostream& operator<< (std::ostream& o, const Module::Vector3& v)
{
	o << "Vector3(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
	return o;
}
*/
}
#endif