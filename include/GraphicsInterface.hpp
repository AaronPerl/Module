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
class GameObject;
class GraphicsContext;
class PolygonContainer;
class GraphicsCallback;

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
		
		Book<float> allVertices;				// all vertices (x, y then z) stored in a contiguous array to improve caching
		Book<float> allNormals;					// all vertex normals, 1 to 1 with vertices
		Book<Mesh> allMeshes;					// same for meshes, though they matter less
		std::vector<GraphicsCallback*> graphicsCallbacks;
		std::vector<InputCallback*> inputCallbacks;
		
		void start();
		void run(); //overrides ThreadObject::run()
		void preRender();
		void postRender();
		
		void mousePressed(uint16_t x, uint16_t y);
		void mouseReleased(uint16_t x, uint16_t y);
		void mouseMoved(uint16_t x, uint16_t y, int16_t dx, int16_t dy);
		
		void keyPressed(uint8_t key);
		void keyReleased(uint8_t key);
		
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
		unsigned int getVertexIndex(Mesh* m) const;		// returns this mesh's starting index in its book of vertices
		unsigned int getNormalIndex(Mesh* m) const;		// returns this mesh's starting index in its book of vertex normals
		unsigned int getNumVertices(Mesh* m) const;		// returns the number of vertices that compose this mesh
		
	public:
		GraphicsInterface();
		GraphicsInterface(unsigned int set_fps);
		
		virtual Mesh* createMesh(Vector3* vertices, Vector3* normals, unsigned int num_vertices, const std::string& name);
		virtual Mesh* createMesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::string& name);
		//virtual Mesh* copyMesh(Mesh* other);
		virtual Mesh* loadMeshFromFile(const std::string& meshname, const std::string& filename, bool flipFaces = false) = 0;
		
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

inline unsigned int GraphicsInterface::getVertexIndex(Mesh* m) const
{
	return m->vertexIndex;
}

inline unsigned int GraphicsInterface::getNormalIndex(Mesh* m) const
{
	return m->normalIndex;
}

inline unsigned int GraphicsInterface::getNumVertices(Mesh* m) const
{
	return m->numVertices;
}

}

#endif
