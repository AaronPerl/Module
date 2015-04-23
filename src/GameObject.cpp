#include "GameObject.hpp"

using Module::Vector3;
using Module::Quaternion;
using Module::TransformObject;

using Module::GameObject;

void GameObject::setPosition(const Vector3& newPos)
{
	if (tObj)
		tObj->setPosition(newPos);
	else
		pos = newPos;
}

void GameObject::setRotation(const Quaternion& newRot)
{
	if (tObj)
		tObj->setRotation(newRot);
	else
		rot = newRot;
}