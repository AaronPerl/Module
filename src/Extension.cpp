#include "Extension.hpp"
#include "ModuleGame.hpp"

#include <typeinfo>

using namespace Module;

Extension::Extension(ModuleGame* game)
{
	game_ = game;
	game_->getComponentManager()->registerExtension(this);
}

void Extension::registerComponent(const char* componentType)
{
	componentTypes.push_back(componentType);
	game_->getComponentManager()->registerComponent(this, componentType);
}

void Extension::registerComponent(Component* component)
{
	registerComponent(typeid(component).name());
}