#include "Physics.hpp"

using namespace Module;

void Physics::spawnThreads()
{
	
}

Physics::Physics(ModuleGame* game) : Extension(game)
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