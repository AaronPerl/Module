#include "Vector2.hpp"

using Module::Vector2;

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float _x, float _y) : x(_x),y(_y) {}

/** Performs scalar multiplication on a Vector2
 * @param scalar The scalar to multiply this by
 * @return a new, resultant Vector2
*/
Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(	x * scalar,
					y * scalar );
}

/** Performs component multiplication on a Vector2
 * @param other The Vector2 to multiply this by
 * @return a new, resultant Vector2
*/
Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2( x * other.x,
					y * other.y );
}

/** Performs scalar multiplication and assinment
 * @param scalar The scalar to multiply this by
 * @return this Vector2
*/
Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return (*this);
}

/** Performs component multiplication and assinment
 * @param other The Vector2 to multiply this by
 * @return this Vector2
*/
Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;
	return (*this);
}

/** Performs vector addition on this Vector2
 * @param other The Vector2 to add to this
 * @return a new, resultant Vector2
*/
Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(	x + other.x,
					y + other.y );
}

/** Performs vector addition and assignment
 * @param other The Vector2 to add to this
 * @return this Vector2
*/
Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return (*this);
}

/** Negates this Vector2
 * @return this Vector2
*/
Vector2 Vector2::operator-() const
{
	return Vector2(-x,-y);
}


/** Performs vector addition on this Vector2
 * @param other The Vector2 to add to this
 * @return a new, resultant Vector2
*/
Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(	x - other.x,
					y - other.y );
}

/** Performs vector subtraction and assinment
 * @param other The Vector2 to subtract from this
 * @return this Vector2
*/
Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return (*this);
}

/** Prints a nicely-formatted string representing this Vector2
 * @param o The ostream to print this Vector2 to
 * @param v The Vector2 to print out
 * @return The original ostream
*/
std::ostream& operator<< (std::ostream& o, const Module::Vector2& v)
{
	o << "Vector2(" << v.getX() << "," << v.getY() << ")";
	return o;
}