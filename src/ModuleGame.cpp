#include "ModuleGame.hpp"
#include <cassert>

Module::ModuleGame::ModuleGame() : graphics(0), threading(0)
{
}

void Module::ModuleGame::attachGraphicsInterface(GraphicsInterface* newGraphics)
{
	newGraphics->game = this;
	graphics = newGraphics;
}

void Module::ModuleGame::attachThreadingInterface(ThreadingInterface* newThreading)
{
	newThreading->game = this;
	threading = newThreading;
}

void Module::ModuleGame::startThread(ThreadObject* obj)
{
	assert(threading!=0);
	threading->startThread(obj);
}

void Module::ModuleGame::start()
{
	graphics->start();
}

bool Module::ModuleGame::isRunning()
{
	assert(graphics!=0);
	return graphics->isRunning();
}