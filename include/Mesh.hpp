#ifndef __MODULE__MESH_HPP__
#define __MODULE__MESH_HPP__

#include "Book.hpp"
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
	Book<Vector3>* vertexBook; // the book containing the vertices of this mesh
	Book<Vector3>* normalBook; // the book containing the normals of this mesh
	unsigned int vertexIndex; // the index of this mesh's first vertex in the vertexBook
	unsigned int normalIndex; // the index of this mesh's first normal in the normalBook
	unsigned int numVertices; // the number of vertices/normals that this mesh has
	std::string name;
	
	Mesh(Book<Vector3>* vb, Book<Vector3>* nb, unsigned int vi, unsigned int ni,
		unsigned int num, std::string meshName) : 
			vertexBook(vb), normalBook(nb), vertexIndex(vi), normalIndex(ni), numVertices(num), name(meshName) {}
public:
	const Vector3& getVertex(unsigned int i) { return (*vertexBook)[vertexIndex + i]; }
	const Vector3& getNormal(unsigned int i) { return (*normalBook)[normalIndex + i]; }
	
	friend class GraphicsInterface;
};
	
}

#endif