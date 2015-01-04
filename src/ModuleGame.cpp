#include "ModuleGame.hpp"

Module::ModuleGame::ModuleGame() : graphics(0)
{
}

void Module::ModuleGame::attachGraphicsInterface(GraphicsInterface* newGraphics)
{
	graphics = newGraphics;
}