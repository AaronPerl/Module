#include "Extension.hpp"
#include "ModuleGame.hpp"

#include <stdexcept>
#include <typeinfo>

using namespace Module;

void Extension::setGame(ModuleGame* game)
{
	if (game_ != NULL)
		throw std::runtime_error("Attempted to bind an extension to a game after it has already been bound!");
	game_ = game;
}

void Extension::registerComponent(const char* componentType)
{
	if (game_ == NULL)
		throw std::runtime_error("Extension attempted to register component without being linked to a game!");
	componentTypes.push_back(componentType);
	game_->registerComponent(this, componentType);
}

void Extension::registerComponent(Component* component)
{
	registerComponent(typeid(component).name());
}