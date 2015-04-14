#ifndef __MODULE__MESH_HPP__
#define __MODULE__MESH_HPP__

#include "GraphicsInterface.hpp"
#include <string>
#include <cstdlib>

namespace Module {

class Vector3;

// Currently, Module does not allow for vertex indexing. This is because
// vertex indexing means each vertex can only have one normal for all uses of that vertex.
// You can have vertex normals with indexing, but that involves unpacking the vertices and
// essentially not using indexing, meaning that the index system's overhead still exists
// without its functionality being used.
class Mesh {
private:
	Vector3* vertices;
	Vector3* normals;
	unsigned int numVertices;
	std::string name;
	
	Mesh(Vector3* v, Vector3* n, unsigned int num, std::string meshName) :
		vertices(v), normals(n), numVertices(num), name(meshName) {}
public:
	Vector3* getVertices() { return vertices; }
	
	friend class GraphicsInterface;
};
	
}

#endif