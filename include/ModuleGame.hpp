#ifndef __MODULE__MODULEGAME_HPP__
#define __MODULE__MODULEGAME_HPP__

#include "GraphicsInterface.hpp"
#include "ThreadingInterface.hpp"
#include "AudioInterface.hpp"

namespace Module {

// The main class of Module. The ModuleGame class represents the core of Module. Its functionality ties together
// that of the different interfaces. End users of Module (game developers) control Module through this class and not
// by accessing interfaces, as those are meant to be abstracted away from users. Setting up a ModuleGame instance should
// be the first thing done in a game that uses Module.
class ModuleGame {
private:
	GraphicsInterface* graphics;
	AudioInterface* audio;
	ThreadingInterface* threading;
	
	Book<GameObject> objects; // The book of all GameObjects
public:
	ModuleGame();
	
	void attachGraphicsInterface(GraphicsInterface* newGraphics);
	void attachAudioInterface(AudioInterface* newAudio);
	void attachThreadingInterface(ThreadingInterface* newThreading);
	
	void startThread(ThreadObject* obj);
	
	void start();
	bool isRunning();
	
	// Game Objects
	GameObject* createGameObject();
	Book<GameObject>::size_type numObjects() const;
	GameObject* getGameObject(Book<GameObject>::size_type index);
	const GameObject* getGameObject(Book<GameObject>::size_type index) const;
	
	// Threading
	Mutex* createMutex();
	
	// Graphics
	void setMesh(GameObject* obj, Mesh* mesh);
	unsigned long getMilliseconds();
};

inline Book<GameObject>::size_type ModuleGame::numObjects() const
{
	return objects.size();
}

inline GameObject* ModuleGame::getGameObject(Book<GameObject>::size_type index)
{
	return &objects[index];
}

inline const GameObject* ModuleGame::getGameObject(Book<GameObject>::size_type index) const
{
	return &objects[index];
}

inline Mutex* ModuleGame::createMutex()
{
	return threading->createMutex();
}

inline void ModuleGame::setMesh(GameObject* obj, Mesh* mesh)
{
	obj->mesh = mesh;
}

inline unsigned long ModuleGame::getMilliseconds()
{
	return graphics->getMilliseconds();
}

}

#endif