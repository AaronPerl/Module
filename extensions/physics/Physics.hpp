#ifndef __PHYSICS_HPP__
#define __PHYSICS_HPP__

#include <ModuleDefines.hpp>
#include <ModuleGame.hpp>
#include <ThreadObject.hpp>
#include <Extension.hpp>

//#include <btBulletDynamicsCommon.h>

class btBroadphaseInterface;
class btCollisionConfiguration;
class btCollisionDispatcher;
class btConstraintSolver;
class btDynamicsWorld;

namespace Module {

/**
 * An extension that incorporates bullet physics into the Module Game Engine.
 */
class Physics : public Extension, public ThreadObject
{
protected:
	const static std::string  NAME;
	const static std::string  VERSION;
	const static int          MAX_SUB_STEPS;
	const static float        FIXED_TIME_STEP;
	
	btBroadphaseInterface* broadphase;
	btCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btConstraintSolver* solver;
	btDynamicsWorld* dynamicsWorld;
	
	void run(); // Overrides ThreadObject::run
	
	const char* getName() { return NAME.c_str(); }
	const char* getVersion() { return VERSION.c_str(); }
	
	void registerComponents() {}
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