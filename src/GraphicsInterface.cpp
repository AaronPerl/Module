#include "ModuleGame.hpp"
#include "GraphicsInterface.hpp"

void Module::GraphicsInterface::start()
{
	game->startThread(this);
}

void Module::GraphicsInterface::run()
{
	unsigned long prevTime = getMilliseconds();
	createWindow();
	while (1)
	{
		renderFrame();
		while (getMilliseconds() - prevTime < 1000/fps);
	}
}