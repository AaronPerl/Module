#include <cmath>
#include <cassert>
#include "Quaternion.hpp"
#include "Vector3.hpp"

using Module::Vector3;

using Module::Quaternion;

Quaternion::Quaternion() : x(0),y(0),z(0),w(1) {}

Quaternion::Quaternion(float _x, float _y, float _z, float _w) : x(_x),y(_y),z(_z),w(_w) {}

Quaternion::Quaternion(Vector3 axis, float angle) 
{
	float sindiv2 = sin(angle/2);
	float cosdiv2 = cos(angle/2);
	x = axis.getX() * sindiv2;
	y = axis.getY() * sindiv2;
	z = axis.getZ() * sindiv2;
	w = cosdiv2;
}

Quaternion Quaternion::operator* (const Quaternion& other) const // quaternion multiplication
{
	return Quaternion(	w * other.x + x * other.w + y * other.z - z * other.y,
						w * other.y - x * other.z + y * other.w + z * other.x,
						w * other.z + x * other.y - y * other.x + z * other.w,
						w * other.w - x * other.x - y * other.y - z * other.z);
}

Quaternion& Quaternion::operator*= (const Quaternion& other) // quaternion multiplication assignment
{
	float newx = w * other.x + x * other.w + y * other.z - z * other.y;
	float newy = w * other.y - x * other.z + y * other.w + z * other.x;
	float newz = w * other.z + x * other.y - y * other.x + z * other.w;
	float neww = w * other.w - x * other.x - y * other.y - z * other.z;
	x = newx;
	y = newy;
	z = newz;
	w = neww;
	return (*this);
}

Quaternion Quaternion::quatpow(float exponent) const // power
{
	float vmagnitude_squared = x*x + y*y + z*z;
	float magnitudepow = pow(sqrt(w*w + vmagnitude_squared),exponent);
	float vmagnitude = sqrt(vmagnitude_squared);
	float thetadiv2 = atan2(w, vmagnitude);
	float vec_factor = magnitudepow * sin(exponent*thetadiv2)/vmagnitude;
	return Quaternion(	vec_factor * x,
						vec_factor * y,
						vec_factor * z,
						magnitudepow * cos(exponent*thetadiv2));
}

Quaternion Quaternion::unitpow(float exponent) const // power of unit quaternion, use with caution
{
	assert(std::abs(x*x + y*y + z*z + w*w-1)<0.01);
	float thetadiv2 = acos(w);
	float vec_factor = sin(exponent*thetadiv2)/sin(thetadiv2);
	return Quaternion(	vec_factor * x,
						vec_factor * y,
						vec_factor * z,
						cos(exponent*thetadiv2));
}

Quaternion Quaternion::inverse() const // inverse/conjugate quaternion
{
	return Quaternion(-x,-y,-z,w);
}

Quaternion Quaternion::unit() const // unit quaternion
{
	float magnitude = sqrt(w*w + x*x + y*y + z*z);
	return Quaternion(x/magnitude, y/magnitude, z/magnitude, w/magnitude);
}

Quaternion& Quaternion::normalize() // unit quaternion assignment
{
	float magnitude = sqrt(w*w + x*x + y*y + z*z);
	w/=magnitude;
	x/=magnitude;
	y/=magnitude;
	z/=magnitude;
	return (*this);	
}

Quaternion Module::slerp(const Quaternion& a, const Quaternion& b, float t) // spherical linear interpolation
{
	// slerp = a * (inverse(a) * b) ^ t
	// c = inverse(a) * b
	Quaternion c = a.inverse() * b;
	Quaternion c_to_t = c.unitpow(t);
	return a * c_to_t;
}

std::ostream& operator<< (std::ostream& o, const Quaternion& q) // ostream insertion operator
{
	o << "Quaternion(" << q.getX() << "," << q.getY() << "," << q.getZ() << "," << q.getW() << ")";
	return o;
}