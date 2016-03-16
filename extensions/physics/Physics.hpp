#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include <ModuleDefines.hpp>
#include <ModuleGame.hpp>
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
	const static std::string  NAME;
	const static std::string  VERSION;
	const static int          MAX_SUB_STEPS;
	const static btScalar     FIXED_TIME_STEP;
	
	btBroadphaseInterface* broadphase;
	btCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btConstraintSolver* solver;
	btDynamicsWorld* dynamicsWorld;
	
	void run(); // Overrides ThreadObject::run
	
	const std::string& getName() { return NAME; }
	const std::string& getVersion() { return VERSION; }
	
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