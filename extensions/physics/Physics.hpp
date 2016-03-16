#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include <ModuleDefines.hpp>
#include <ThreadObject.hpp>
#include <Extension.hpp>

#include <btBulletDynamicsCommon.h>

namespace Module {

/**
 * An extension that incorporates bullet physics into the Module Game Engine.
 */
class Physics : Extension, ThreadObject
{
protected:
	btBroadphaseInterface* broadphase;
	btCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btConstraintSolver* solver;
	btDynamicsWorld* dynamicsWorld;
	
	void run(); // Overrides ThreadObject::run
	
	const std::string& getName() { return "Bullet Physics Extension"; }
	const std::string& getVersion() { return "0.0.1"; }
	
	void attachGraphicsCallbacks() {}
	void attachInputCallbacks() {}
	void attachAudioCallbacks() {}
	void spawnThreads();
public:
	Physics(ModuleGame* game);
	~Physics();
};

}

#endif