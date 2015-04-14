#ifndef __MODULE__VECTOR_HPP__
#define __MODULE__VECTOR_HPP__

#include <iostream>

namespace Module {

class Quaternion;

// A simple 3D Vector class. Not optimized and may be replaced in the future to use a faster alternative.
class Vector3 {
private:
	float x,y,z;
public:
	
	Vector3();
	Vector3(float x, float y, float z);
	
	Vector3 operator*(float scalar) const;			// scalar multiplication
	Vector3 operator*(const Vector3& other) const; // component-wise multiplication
	Vector3& operator*=(float scalar);				// scalar multiplication assignment
	Vector3& operator*=(const Vector3& other);		// component-wise multiplication assignment
	Vector3 operator+(const Vector3& other) const; 	// vector addition
	Vector3& operator+=(const Vector3& other); 		// addition assignment
	Vector3 operator-() const; 						// negation
	Vector3 operator-(const Vector3& other) const;	// vector subtraction
	Vector3& operator-=(const Vector3& other);		// subtraction assignment
	
	Vector3 rotate(const Quaternion& other) const;	// quaternion rotation
	
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	
	Vector3 cross(const Vector3& other) const; 		// vector cross product	
	float dot(const Vector3& other) const; 			// vector dot product	
	
	
};

}

std::ostream& operator<< (std::ostream& o, const Module::Vector3& v);	// ostream insertion operator

#endif