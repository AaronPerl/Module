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
	Book<GameObject>::size_type numObjects() { return objects.size(); }
	GameObject* getGameObject(Book<GameObject>::size_type index) { return &objects[index]; }
	
	// Threading
	Mutex* createMutex() { return threading->createMutex(); }
	
	// Graphics
	void setMesh(GameObject* obj, Mesh* mesh) { obj->mesh = mesh; }
	unsigned long getMilliseconds() { return graphics->getMilliseconds(); }
};

}

#endif