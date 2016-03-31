#ifndef __MODULE__GAMEOBJECT_HPP__
#define __MODULE__GAMEOBJECT_HPP__

#include "ModuleDefines.hpp"
#include "Sound.hpp"
#include "SoundClip.hpp"
#include "Book.hpp"
#include "TransformObject.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

#include <EASTL/vector.h>

namespace Module {

/**
 * One of the core classes in Module. The GameObject represents any object in the game world (though not terrain).
 * Being that Module is a component-based engine, the GameObject class can have contain of many different components.
 * At the current moment, this list is finite and hard-coded, being represented by pointers to objects. In the future,
 * with the addition of an extension system, this list could be joined with a dynamic container of generic components used by extensions.
 */
class GameObject {
protected:
	ModuleGame* game;
	TransformObject* tObj;
	Mesh* mesh;
	Texture* texture;
	Vector3 pos;
	Quaternion rot;
	eastl::vector<Component*> components;
	GameObject(ModuleGame* g) : game(g), tObj(0), mesh(0), texture(0) {}
	GameObject() : game(0), tObj(0), mesh(0), texture(0) {} // EMpty constructor to enable use in a Book
public:
	const Vector3& getPosition() const		{ return tObj ? tObj->getPosition() : pos; }
	const Quaternion& getRotation() const	{ return tObj ? tObj->getRotation() : rot; }
	void setPosition(const Vector3& newPos);
	void setRotation(const Quaternion& newRot);
	
	TransformObject* getTransform() { return tObj; }
	void setTransform(TransformObject* t) { tObj = t; }
	
	Mesh* getMesh() { return mesh; }
	Texture* getTexture() { return texture; }
	
	// Audio
	Sound* playSound(SoundClip*);											// Plays a Sound
	SoundClip* loadSoundClip(const eastl::string&, const eastl::string&);	// Loads SoundClip
	void unloadSoundClip(SoundClip*);										// Unloads SoundClip

	template<class T>
	T* getComponent();
	
	template<class T>
	T* getComponent(unsigned int index);
	
	friend class ModuleGame;
	friend class Book<GameObject>;
};

}

/**
 * Finds the first component of type T in this GameObject 
 * @return A pointer to the first component of type T in this GameObject,
 * NULL if none exist of type T
 */
template<class T>
T* Module::GameObject::getComponent()
{
	for (unsigned int i = 0; i < components.size(); i++)
	{
		T* curComponent = dynamic_cast<T*>(components[0]);
		if (curComponent != NULL)
		{
			return curComponent;
		}
	}
	return NULL;
}

/**
 * Finds the first component of type T in this GameObject of the given index
 * i.e. if there are 2 components of type T in this GameObject and this is called with
 * index = 1, then it will return the second component of type T. Order is based on
 * when the components were added to this GameObject.
 * @return A pointer to the component of type T in this GameObject with the given index,
 * NULL if there is no component of type T with the given index
 */
template<class T>
T* Module::GameObject::getComponent(unsigned int index)
{
	unsigned int componentsFound = 0;
	for (unsigned int i = 0; i < components.size(); i++)
	{
		T* curComponent = dynamic_cast<T*>(components[0]);
		if (curComponent != NULL)
		{
			if (componentsFound == index)
				return curComponent;
				
			componentsFound++;
		}
	}
}

#endif