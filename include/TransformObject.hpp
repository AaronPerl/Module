#ifndef __MODULE__TRANSFORMOBJECT_HPP__
#define __MODULE__TRANSFORMOBJECT_HPP__

namespace Module {

class Vector3;
class Quaternion;

// The TransformObject class is a pure virtual class. It is used to
// add some behavior to the position/rotation (transform) of GameObjects.
// If a GameObject's TransformObject pointer is not NULL, then Module will use
// the TransformObject's getPosition/Rotation methods instead. Likewise, GameObject's
// setPosition/Rotation methods will pass through to the TransformObject if the pointer is not NULL.
class TransformObject {
protected:
public:
	virtual const Vector3& getPosition() const = 0;
	virtual const Quaternion& getRotation() const = 0;
	virtual void setPosition(const Vector3& newPos) = 0;
	virtual void setRotation(const Quaternion& newRot) = 0;

};

}

#endif