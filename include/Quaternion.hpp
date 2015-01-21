#ifndef __MODULE__QUATERNION_HPP__
#define __MODULE__QUATERNION_HPP__

#include <iostream>

namespace Module {

class Vector3;

class Quaternion {
private:
	float x;
	float y;
	float z;
	float w;
public:
	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(Vector3 axis, float angle);
	
	Quaternion operator* (const Quaternion& other) const;	// quaternion multiplication
	Quaternion& operator*= (const Quaternion& other);		// quaternion multiplication assignment
	Quaternion quatpow(float exponent) const; 				// power of any quaternion
	Quaternion unitpow(float exponent) const;				// power of unit quaternion, use with caution
	//Quaternion& powAssign(float exponent); 				// power assignment

	Quaternion inverse() const;								// inverse/conjugate quaternion
	Quaternion unit() const;								// unit quaternion
	Quaternion& normalize();								// unit quaternion assignment
	
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	float getW() const { return w; }	
	
};


Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);		// spherical linear interpolation

}

std::ostream& operator<< (std::ostream& o, const Module::Quaternion& q);	// ostream insertion operator

#endif