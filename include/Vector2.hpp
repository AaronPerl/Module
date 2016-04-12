#ifndef __MODULE__VECTOR2_HPP__
#define __MODULE__VECTOR2_HPP__

#include <iostream>

namespace Module {

// A simple 2D Vector class. Not optimized
class Vector2
{
	private:
		float x;	/**< The x-coordinate */
		float y;	/**< The y-coordinate */
		
	public:
		static const Vector2 ZERO;
		static const Vector2 UP;
		static const Vector2 DOWN;
		static const Vector2 RIGHT;
		static const Vector2 LEFT;
		
		Vector2();										// default constructor
		Vector2(float x, float y);						// constructor with arguments
		
		Vector2 operator*(float scalar) const;			// scalar multiplication
		Vector2 operator*(const Vector2& other) const;	// component-wise multiplication
		Vector2& operator*=(float scalar);				// scalar multiplication assignment
		Vector2& operator*=(const Vector2& other);		// component-wise multiplication assignment
		Vector2 operator+(const Vector2& other) const; 	// vector addition
		Vector2& operator+=(const Vector2& other); 		// addition assignment
		Vector2 operator-() const; 						// negation
		Vector2 operator-(const Vector2& other) const;	// vector subtraction
		Vector2& operator-=(const Vector2& other);		// subtraction assignment
	
		float getX() const;								// A getter for x
		float getY() const;								// A getter for y
};

/** Gets the x-coordinate of this Vector2
 * @return The x-coordinate of this Vector2
*/
inline float Vector2::getX() const
{
	return x;
}

/** Gets the y-coordinate of this Vector2
 * @return The y-coordinate of this Vector2
*/
inline float Vector2::getY() const
{
	return y;
}

}



#endif