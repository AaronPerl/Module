#include "ModuleGame.hpp"
#include <cassert>

Module::ModuleGame::ModuleGame() : graphics(0)
{
}

void Module::ModuleGame::attachGraphicsInterface(GraphicsInterface* newGraphics)
{
	graphics = newGraphics;
}

void Module::ModuleGame::attachThreadingInterface(ThreadingInterface* newThreading)
{
	threading = newThreading;
}

void Module::ModuleGame::startThread(ThreadObject* obj)
{
	assert(threading!=0);
	threading->startThread(obj);
}