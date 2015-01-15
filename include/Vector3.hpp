#ifndef __MODULE__VECTOR_HPP__
#define __MODULE__VECTOR_HPP__

namespace Module {

class Vector3 {
private:
	float _x,_y,_z;
public:
	Vector3() : _x(0),_y(0),_z(0) {}
	Vector3(float x, float y, float z) : _x(x),_y(y),_z(z) {}
	
	Vector3 operator*(const Vector3& other) // component-wise multiplication
	{
		return Vector3( x * other.x,
						y * other.y,
						z * other.z);
	}
	
	Vector3 operator+(const Vector3& other) // vector addition
	{
		return Vector3(	x + other.x,
						y + other.y,
						z + other.z);
	}
	
	Vector3 operator-() // negation
	{
		return Vector3(-x,-y,-z);
	}
	
	Vector3 cross(const Vector3& other) // vector cross product
	{
		return Vector3(	y * other.z - z * other.y,
						z * other.x - x * other.z,
						x * other.y - y * other.x);
	}
	
	float dot(const Vector3& other) // vector dot product
	{
		return x * other.x + y * other.y + z * other.z;
	}
	
	Vector3& operator+=(const Vector3& other) // addition assignment
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return (*this);
	}
	
	
};

}

#endif