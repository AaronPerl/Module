#ifndef __MODULE__GRAPHICSINTERFACE_HPP__
#define __MODULE__GRAPHICSINTERFACE_HPP__

#include "ThreadObject.hpp"
#include "DynamicArray.hpp"
#include "ModuleGame.hpp"
#include <string>

namespace Module
{
	class Mesh;
	class Vector3;

	class GraphicsInterface : ThreadObject
	{
		friend class ModuleGame;
		
		protected:
			unsigned int fps;
			ModuleGame* game;
			
			DynamicArray<Vector3> allVertices;	// all vertices stored in a contiguous array to improve caching
			DynamicArray<Mesh> allMeshes;		// same for meshes, though they matter less
			
			void start();
			void run(); //overrides ThreadObject::run()
			
			// IMPLEMENT THESE //
			virtual void createWindow() = 0; 				// initialization and window creation
			virtual void renderFrame() = 0;					// render individual frame
			virtual unsigned long getMilliseconds() = 0;	// get time since initialization
			
		public:
			GraphicsInterface() : fps(60) {}
			GraphicsInterface(unsigned int set_fps) : fps(set_fps) {}
			
			virtual Mesh* createMesh(Vector3* vertices, unsigned int num_vertices, const std::string& name);
			virtual Mesh* createMesh(const DynamicArray<Vector3>& vertices, const std::string& name);
			
			virtual Mesh* copyMesh(Mesh* other);
			
	};
}

#endif