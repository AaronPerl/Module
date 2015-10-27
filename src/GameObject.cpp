#include "GameObject.hpp"
#include "ModuleGame.hpp"

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

/** Plays a Sound.
 * @param clip A pointer to the SoundClip that the Sound will be of.
 * @return A pointer to the Sound, which is currently playing.
*/
// CAN'T inline this properly without circular dependencies
Module::Sound* GameObject::playSound(Module::SoundClip* clip)
{
	return game->playSound(clip,this);
}

/** Loads a SoundClip into memory.
 * @param name The name of the SoundClip, ie: "explosion."
 * @param fileName The name of the file to be loaded from.
 * @return A pointer to the loaded SoundClip.
*/
inline Module::SoundClip* GameObject::loadSoundClip(const std::string& name, const std::string& fileName)
{
	return game->loadSoundClip(name,fileName);
}
