#ifndef __MODULE__GRAPHICSINTERFACE_HPP__
#define __MODULE__GRAPHICSINTERFACE_HPP__

#include "ModuleDefines.hpp"
#include "Mesh.hpp"
#include "ThreadObject.hpp"
#include "KeyCodes.hpp"
#include "PolygonContainer.hpp"
#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <stdint.h>

namespace Module
{

/** 
 * The GraphicsInterface is one of Module's four core interfaces. It manages rendering
 * and user input. Implementations of the GraphicsInterface are responsible for drawing
 * the world and triggering the attached graphics and input callbacks.
 */
class GraphicsInterface : ThreadObject
{
	friend class ModuleGame;
	friend class GraphicsContext;
	
	protected:
		unsigned int fps;
		ModuleGame* game;
		GameObject* camera;
		bool keyStates[222];
		
		Book<float> allVertices;				// all vertices (x, y then z) stored in a contiguous array to improve caching
		Book<float> allNormals;					// all vertex normals, 1 to 1 with vertices
		Book<float> allUVs;					// all texture coordinates
		Book<Mesh> allMeshes;					// same for meshes, though they matter less
		Book<PolygonContainer> allPolygons;		// same for polygon containers
		eastl::vector<GraphicsCallback*> graphicsCallbacks;
		eastl::vector<InputCallback*> inputCallbacks;
		
		void start();
		void run(); //overrides ThreadObject::run()
		void preRender();
		void postRender();
		
		void mousePressed(uint8_t button, uint16_t x, uint16_t y);
		void mouseReleased(uint8_t button, uint16_t x, uint16_t y);
		void mouseMoved(uint16_t x, uint16_t y, int16_t dx, int16_t dy);
		
		void keyPressed(KeyCode::Code code, char keyChar);
		void keyReleased(KeyCode::Code code, char keyChar);
		
		bool checkKeyState(KeyCode::Code code) const { return keyStates[code]; }
		
		// IMPLEMENT THESE //
		virtual void createWindow() = 0;            	// initialization and window creation
		virtual void renderFrame() = 0;             	// render individual frame
		virtual void swapBuffers() = 0;
		virtual unsigned long getMilliseconds() = 0;	// get time since initialization
		virtual bool isRunning() = 0;	
		virtual void drawPolygons2D(const PolygonContainer& polygons) = 0;
		
		// FRIENDSHIP WRAPPERS //
		Book<float>* getVertexBook(Mesh* m) const;		// returns the book that contains the vertices the ones for this mesh
		Book<float>* getNormalBook(Mesh* m) const;		// returns the book that contains the vertex normals for this mesh
		Book<float>* getUVBook(Mesh* m) const;
		Book<float>::size_type getVertexIndex(Mesh* m) const;		// returns this mesh's starting index in its book of vertices
		Book<float>::size_type getNormalIndex(Mesh* m) const;		// returns this mesh's starting index in its book of vertex normals
		Book<float>::size_type getUVIndex(Mesh* m) const;
		Book<float>::size_type getNumVertices(Mesh* m) const;		// returns the number of vertices that compose this mesh
		
	public:
		GraphicsInterface();
		GraphicsInterface(unsigned int set_fps);
		
		Mesh* createMesh(Vector3* vertices, Vector3* normals, float* uvs, unsigned int num_vertices, const eastl::string& name);
		Mesh* createMesh(const eastl::vector<Vector3>& vertices, const eastl::vector<Vector3>& normals,
		                 const eastl::vector<float>& uvs, const eastl::string& name);
		//virtual Mesh* copyMesh(Mesh* other);
		virtual Mesh* loadMeshFromFile(const eastl::string& meshname, const eastl::string& filename, bool flipFaces = false) = 0;
		virtual Texture* loadTexture(const eastl::string& filename) = 0;
		
		PolygonContainer* createPolygonContainer();
		
		virtual void setCamera(GameObject* obj) { camera = obj; }
		
		void addGraphicsCallback(GraphicsCallback* g);
		void addInputCallback(InputCallback* g);
};

inline Book<float>* GraphicsInterface::getVertexBook(Mesh* m) const
{
	return m->vertexBook;
}	

inline Book<float>* GraphicsInterface::getNormalBook(Mesh* m) const
{
	return m->normalBook;
}	

inline Book<float>* GraphicsInterface::getUVBook(Mesh* m) const
{
	return m->uvBook;
}

inline Book<float>::size_type GraphicsInterface::getVertexIndex(Mesh* m) const
{
	return m->vertexIndex;
}

inline Book<float>::size_type GraphicsInterface::getNormalIndex(Mesh* m) const
{
	return m->normalIndex;
}

inline Book<float>::size_type GraphicsInterface::getUVIndex(Mesh* m) const
{
	return m->uvIndex;
}

inline Book<float>::size_type GraphicsInterface::getNumVertices(Mesh* m) const
{
	return m->numVertices;
}

}

#endif
