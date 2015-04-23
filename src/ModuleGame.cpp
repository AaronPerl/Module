#include "ModuleGame.hpp"
#include <cassert>

Module::ModuleGame::ModuleGame() : graphics(0), audio(0), threading(0)
{
}

Module::GameObject* Module::ModuleGame::createGameObject()
{
	objects.push_back(GameObject());
	return &objects.back();
}

void Module::ModuleGame::attachGraphicsInterface(GraphicsInterface* newGraphics)
{
	newGraphics->game = this;
	graphics = newGraphics;
}

void Module::ModuleGame::attachAudioInterface(AudioInterface* newAudio)
{
	newAudio->game = this;
	audio = newAudio;
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
	if(graphics)
		graphics->start();
	if(audio)
		audio->start();
}

bool Module::ModuleGame::isRunning()
{
	assert(graphics!=0);
	return graphics->isRunning();
}