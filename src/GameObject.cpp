#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "PhysicsObject.hpp"

#include "GameObject.hpp"

using Module::Vector3;
using Module::Quaternion;
using Module::PhysicsObject;

using Module::GameObject;

Vector3 GameObject::getPosition()
{
	return pObj->getPosition();
};

Quaternion GameObject::getRotation()
{
	return pObj->getRotation();
}