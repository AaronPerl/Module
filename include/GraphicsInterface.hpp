#ifndef __MODULE__GRAPHICSINTERFACE_HPP__
#define __MODULE__GRAPHICSINTERFACE_HPP__

#include "Mesh.hpp"
#include "ThreadObject.hpp"
#include "Book.hpp"
#include "Vector3.hpp"
#include <string>
#include <vector>

namespace Module
{
	class Mesh;
	class ModuleGame;

	class GraphicsInterface : ThreadObject
	{
		friend class ModuleGame;
		
		protected:
			unsigned int fps;
			ModuleGame* game;
			
			Book<float> allVertices;	// all vertices (x, y then z) stored in a contiguous array to improve caching
			Book<float> allNormals;		// all vertex normals, 1 to 1 with vertices
			Book<Mesh> allMeshes;		// same for meshes, though they matter less
			
			void start();
			void run(); //overrides ThreadObject::run()
			
			// IMPLEMENT THESE //
			virtual void createWindow() = 0; 				// initialization and window creation
			virtual void renderFrame() = 0;					// render individual frame
			virtual unsigned long getMilliseconds() = 0;	// get time since initialization
			virtual bool isRunning() = 0;
			
			// FRIENDSHIP WRAPPERS
			Book<float>* getVertexBook(Mesh* m) { return m->vertexBook; }
			Book<float>* getNormalBook(Mesh* m) { return m->normalBook; }
			unsigned int getVertexIndex(Mesh* m) { return m->vertexIndex; }
			unsigned int getNormalIndex(Mesh* m) { return m->normalIndex; }
			unsigned int getNumVertices(Mesh* m) { return m->numVertices; }
			
		public:
			GraphicsInterface();
			GraphicsInterface(unsigned int set_fps);
			
			virtual Mesh* createMesh(Vector3* vertices, Vector3* normals, unsigned int num_vertices, const std::string& name);
			virtual Mesh* createMesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::string& name);
			
			//virtual Mesh* copyMesh(Mesh* other);
			
	};
}

#endif
