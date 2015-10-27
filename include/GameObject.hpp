#ifndef __MODULE__GAMEOBJECT_HPP__
#define __MODULE__GAMEOBJECT_HPP__

#include "ModuleDefines.hpp"
#include "Book.hpp"
#include "TransformObject.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

namespace Module {

class ModuleGame;
class Mesh;

// One of the core classes in Module. The GameObject represents any object in the game world (though not terrain).
// Being that Module is a component-based engine, the GameObject class can have contain of many different components.
// At the current moment, this list is finite and hard-coded, being represented by pointers to objects. In the future,
// with the addition of an extension system, this list could be joined with a dynamic container of generic components used by extensions.
class GameObject {
protected:
	ModuleGame* game;
	TransformObject* tObj;
	Mesh* mesh;
	Vector3 pos;
	Quaternion rot;
	GameObject(ModuleGame* g) : game(g), tObj(0), mesh(0) {}
	GameObject() : game(0), tObj(0), mesh(0) {} // EMpty constructor to enable use in a Book
public:
	const Vector3& getPosition() const		{ return tObj ? tObj->getPosition() : pos; }
	const Quaternion& getRotation() const	{ return tObj ? tObj->getRotation() : rot; }
	void setPosition(const Vector3& newPos);
	void setRotation(const Quaternion& newRot);
	
	TransformObject* getTransform() { return tObj; }
	void setTransform(TransformObject* t) { tObj = t; }
	
	Mesh* getMesh() { return mesh; }
	
	// Audio
	Sound* playSound(SoundClip*);											// Plays a Sound
	SoundClip* loadSoundClip(const std::string&, const std::string&);		// Loads SoundClip
	void unloadSoundClip(SoundClip*);										// Unloads SoundClip
	
	friend class ModuleGame;
	friend class Book<GameObject>;
};

}

#endif