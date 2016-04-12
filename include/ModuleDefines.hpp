#ifndef __MODULEDEFINES_HPP__
#define __MODULEDEFINES_HPP__

#include <iostream>
#include <EASTL/string.h>

namespace Module
{
	void Log(const eastl::string& info);
	
	class ModuleGame;
		class GameObject;
		class Vector3;
		class Quaternion;
		class TransformObject;
	class Extension;
		class ComponentManager;
		class Component;
	class GraphicsInterface;
		class GraphicsCallback;
		class InputCallback;
		class GraphicsContext;
		class Mesh;
		class Texture;
		class Color;
		class PolygonContainer;
	class AudioInterface;
		class Sound;
		class SoundClip;
	class ThreadingInterface;
		class ThreadData;
		class ThreadObject;
		class Mutex;
	class Extension;
	//class NetworkInterface;
}

namespace eastl{
	std::ostream& operator<< (std::ostream& o, const eastl::string& s);
}

#endif