#ifndef __MODULE__COMPONENTMANAGER_HPP__
#define __MODULE__COMPONENTMANAGER_HPP__

#include <typeinfo>

#include <EASTL/vector.h>
#include <EASTL/hash_map.h>

#include "ModuleDefines.hpp"
#include "Extension.hpp"


namespace Module {

/**
 * The ComponentManager class manages the registration of components by extensions.
 * It allows for lookup of the extension that registered a component, as well as
 * looking up all components registered by a given extension.
 */
class ComponentManager {
	private:
		ModuleGame* game_;
		eastl::vector<Extension*> extensions;
		// eastl::hash_map<std::type_info, Extension*> componentMap;
		eastl::hash_map<int, Extension*> componentMap;
		
		void registerComponent(Extension*, const char*);
		void registerExtension(Extension*);
		
		void initializeExtensions();
		
		unsigned long hash(const char*);
	public:

	friend class ModuleGame;
	friend class Extension;
};

}

#endif