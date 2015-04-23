#ifndef __MODULE__MESH_HPP__
#define __MODULE__MESH_HPP__

#include "Book.hpp"
#include "Vector3.hpp"
#include <string>
#include <cstdlib>

namespace Module {

class Vector3;
class GraphicsInterface;

// Currently, Module does not allow for vertex indexing. This is because
// vertex indexing means each vertex can only have one normal for all uses of that vertex (e.g. smooth faces).
// You can have vertex normals with indexing, but that involves unpacking the vertices and
// essentially not using indexing, meaning that the index system's overhead still exists
// without its functionality being used.
class Mesh {
private:
	Book<float>* vertexBook; // the book containing the vertices of this mesh
	Book<float>* normalBook; // the book containing the normals of this mesh
	unsigned int vertexIndex; // the index of this mesh's first vertex in the vertexBook
	unsigned int normalIndex; // the index of this mesh's first normal in the normalBook
	unsigned int numVertices; // the number of vertices/normals that this mesh has
	std::string name;
	Mesh() :
		vertexBook(0), normalBook(0), vertexIndex(0), normalIndex(0), numVertices(0), name("") {}
	Mesh(Book<float>* vb, Book<float>* nb, unsigned int vi, unsigned int ni,
		unsigned int num, std::string meshName) : 
			vertexBook(vb), normalBook(nb), vertexIndex(vi), normalIndex(ni), numVertices(num), name(meshName) {}
public:
	Vector3 getVertex(unsigned int i) { return Vector3((*vertexBook)[vertexIndex + 3 * i], (*vertexBook)[vertexIndex + 3 * i + 1], (*vertexBook)[vertexIndex + 3 * i + 2]); }
	Vector3 getNormal(unsigned int i) { return Vector3((*normalBook)[normalIndex + 3 * i], (*normalBook)[normalIndex + 3 * i + 1], (*normalBook)[normalIndex + 3 * i + 2]); }
	unsigned int getNumVertices() { return numVertices; }
	
	friend class GraphicsInterface;
	friend class Book<Mesh>;
};
	
}

#endif