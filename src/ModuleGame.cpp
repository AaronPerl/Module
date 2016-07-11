#include "ModuleGame.hpp"
#include <cassert>

/**
 * The default constructor of ModuleGame.
 */
Module::ModuleGame::ModuleGame() : graphics(0), audio(0), threading(0)
{
}

/**
 * Creates a new GameObject.
 * @return A pointer to the created GameObject
 */
Module::GameObject* Module::ModuleGame::createGameObject()
{
	objects.push_back(GameObject(this));
	return &objects.back();
}

/**
 * Attaches a GraphicsInterface to this game.
 * @param newGraphics A pointer to the GraphicsInterface to attach to this game
 */
void Module::ModuleGame::attachGraphicsInterface(GraphicsInterface* newGraphics)
{
	newGraphics->game = this;
	graphics = newGraphics;
}

/**
 * Attaches an AudioInterface to this game.
 * @param newAudio A pointer to the AudioInterface to attach to this game
 */
void Module::ModuleGame::attachAudioInterface(AudioInterface* newAudio)
{
	newAudio->game = this;
	audio = newAudio;
}

/**
 * Attaches a ThreadingInterface to this game.
 * @param newThreading A pointer to the ThreadingInterface to attach to this game
 */
void Module::ModuleGame::attachThreadingInterface(ThreadingInterface* newThreading)
{
	newThreading->game = this;
	threading = newThreading;
}

/**
 * Adds a new extension to the game to be initialized at the start of the game.
 * @param extension The extension to add to the game
 */
void Module::ModuleGame::addExtension(Extension* extension)
{
	extension->setGame(this);
	componentManager.registerExtension(extension);
}

/**
 * Calls the run function of a ThreadObject in a newly spawned thread.
 * @param obj The ThreadObject to call the run method of
 */
void Module::ModuleGame::startThread(ThreadObject* obj)
{
	assert(threading!=0);
	threading->startThread(obj);
}

/**
 * Starts the game.
 */
void Module::ModuleGame::start()
{
	componentManager.initializeExtensions();
	
	if(graphics)
		graphics->start();
	if(audio)
		audio->start();
}

/**
 * Checks if the game is running or not.
 * @return Whether or not the game is currently running
 */
bool Module::ModuleGame::isRunning()
{
	assert(graphics!=0);
	return graphics->isRunning();
}