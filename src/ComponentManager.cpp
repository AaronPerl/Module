#include "ComponentManager.hpp"

using namespace Module;

/**
 * Registers a component to a given extension.
 * @param ext The Extension to register the component to
 * @param componentType The type name of the component to register (i.e. PhysicsComponent, etc.)
 */
void ComponentManager::registerComponent(Extension* ext, const char* componentType)
{
	componentMap[hash(componentType)] = ext;
}

/**
 * Registers a new Extension. Automatically called by the Extension constructor
 * @param ext The new Extension to register.
 */
void ComponentManager::registerExtension(Extension* ext)
{
	extensions.push_back(ext);
}

/**
 * Initializes all of the extensions added to the game. This will call each extension's
 * component registration, callback attachment and thread spawning methods.
 */
void ComponentManager::initializeExtensions()
{
	for (eastl::vector<Extension*>::size_type i = 0; i < extensions.size(); i++)
	{
		// For now, the methods are simply called sequentially and thus are only seperated for readability.
		// In the future, the seperation of these methods could be taken utilized for new features.
		Extension* curExtension = extensions[i];
		curExtension -> registerComponents();
		curExtension -> attachGraphicsCallbacks();
		curExtension -> attachInputCallbacks();
		curExtension -> attachAudioCallbacks();
		curExtension -> spawnThreads();
	}
}

/**
 * djb2 hash function, used because hash_maps do not hash c strings.
 * @param str The null terminated string to hash
 * @return The djb2 hash of the given string
 */
unsigned long ComponentManager::hash(const char* str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++) != 0)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}