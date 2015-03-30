#ifndef __MODULE__MESH_HPP__
#define __MODULE__MESH_HPP__

#include "GraphicsInterface.hpp"
#include <string>

namespace Module {

class Vector3;

class Mesh {
private:
	Vector3* vertices;
	unsigned int numVertices;
	std::string name;
	
	Mesh(Vector3* v, unsigned int num, std::string meshName) :
		vertices(v), numVertices(num), name(meshName) {}
public:
	Vector3* getVertices() { return vertices; }
	
	friend class GraphicsInterface;
};
	
}

#endif