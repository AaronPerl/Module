#ifndef __MODULE__VECTOR_HPP__
#define __MODULE__VECTOR_HPP__

namespace Module {

class Vector3 {
private:
	float coords[3];
public:
	const float& x;
	const float& y;
	const float& z;
	
	Vector3();
	Vector3(float _x, float _y, float _z);
	
	Vector3 operator*(const Vector3& other); 		// component-wise multiplication
	Vector3 operator+(const Vector3& other); 		// vector addition
	Vector3& operator+=(const Vector3& other); 		// addition assignment
	Vector3 operator-(); 							// negation
	Vector3 operator-(const Vector3& other); 		// vector subtraction
	Vector3& operator-=(const Vector3& other);		// subtraction assignment
	const float& operator[](int index);				// index

	const float* getCoords();
	
	Vector3 cross(const Vector3& other); 			// vector cross product	
	float dot(const Vector3& other); 				// vector dot product	
	
	
};

}

#endif