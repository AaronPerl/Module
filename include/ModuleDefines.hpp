#ifndef __MODULEDEFINES_HPP__
#define __MODULEDEFINES_HPP__

#include <string>

namespace Module
{	
	void Log(const std::string& info);
	
	class ModuleGame;
		class GameObject;
		class Vector3;
		class Quaternion;
		class TransformObject;
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

#endif