#ifndef __MODULE__PHYSICSOBJECT_HPP__
#define __MODULE__PHYSICSOBJECT_HPP__

namespace Module {

class Vector3;
class Quaternion;

class PhysicsObject {
protected:
public:
	virtual Vector3 getPosition();
	virtual Quaternion getRotation();

};

}

#endif