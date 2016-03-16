#include "Physics.hpp"

using namespace Module;

const std::string  Physics::NAME            = "Bullet Physics Extension";
const std::string  Physics::VERSION         = "0.0.1";
const int          Physics::MAX_SUB_STEPS   = 7;
const btScalar     Physics::FIXED_TIME_STEP = btScalar(1.) / btScalar(60.);

void Physics::spawnThreads()
{
	game_ -> startThread(this);
}

void Physics::run()
{
	unsigned long prevTime = game_ -> getMilliseconds();
	while (game_ -> isRunning())
	{
		unsigned long curTime = game_ -> getMilliseconds();
		
		dynamicsWorld -> stepSimulation((curTime - prevTime) / 1000.0f,
			MAX_SUB_STEPS,
			FIXED_TIME_STEP);
		
		// 60 physics frames per second
		while (game_ -> getMilliseconds() - prevTime < 1000/60);
		
		prevTime = curTime;
	}
}

Physics::Physics(ModuleGame* game_) : Extension(game_)
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(
		dispatcher, broadphase, solver, collisionConfiguration);
}

Physics::~Physics()
{
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}