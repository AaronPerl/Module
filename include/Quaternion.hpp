#ifndef __MODULE__QUATERNION_HPP__
#define __MODULE__QUATERNION_HPP__

#include <iostream>

namespace Module {

class Vector3;

// A simple Quaternion class. Not optimized
class Quaternion
{
	private:
		float x;	/**< The x-value */
		float y;	/**< The y-value */
		float z;	/**< The z-value */
		float w;	/**< The w-value */
		
	public:
		Quaternion();											// default constructor
		Quaternion(float _x, float _y, float _z, float _w);		// donstructor with arguments
		Quaternion(Vector3 axis, float angle);					// constructor with angle and axis
		
		Quaternion operator* (const Quaternion& other) const;	// quaternion multiplication
		Quaternion& operator*= (const Quaternion& other);		// quaternion multiplication assignment
		Quaternion quatpow(float exponent) const; 				// power of any quaternion
		Quaternion unitpow(float exponent) const;				// power of unit quaternion, use with caution
		//Quaternion& powAssign(float exponent); 				// power assignment

		Quaternion inverse() const;								// inverse/conjugate quaternion
		Quaternion unit() const;								// unit quaternion
		Quaternion& normalize();								// unit quaternion assignment
		
		float getX() const;										// A getter for x
		float getY() const;										// A getter for y
		float getZ() const;										// A getter for z
		float getW() const;										// A getter for w
	
};

/** Gets the x-value of this Quaternion
 * @return The x-value of this Quaternion
*/
inline float Quaternion::getX() const
{
	return x;
}

/** Gets the y-value of this Quaternion
 * @return The y-value of this Quaternion
*/
inline float Quaternion::getY() const
{
	return y;
}

/** Gets the z-value of this Quaternion
 * @return The z-value of this Quaternion
*/
inline float Quaternion::getZ() const
{
	return z;
}

/** Gets the w-value of this Quaternion
 * @return The w-value of this Quaternion
*/
inline float Quaternion::getW() const
{
	return w;
}

Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);		// spherical linear interpolation

std::ostream& operator<< (std::ostream& o, const Module::Quaternion& q);	// ostream insertion operator

}



#endif