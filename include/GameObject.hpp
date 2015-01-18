#ifndef __MODULE__GAMEOBJECT_HPP__
#define __MODULE__GAMEOBJECT_HPP__

namespace Module {

class Vector3;
class Quaternion;
class PhysicsObject;

class GameObject {
protected:
	PhysicsObject* pObj;
public:
	Vector3 getPosition();
	Quaternion getRotation();

};

}

#endif