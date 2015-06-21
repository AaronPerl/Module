#ifndef __MODULE__MESH_HPP__
#define __MODULE__MESH_HPP__

#include "Book.hpp"
#include "Vector3.hpp"
#include <string>
#include <cstdlib>
#include <vector>

namespace Module {

class Vector3;
class GraphicsInterface;
class GameObject;

// Currently, Module does not allow for vertex indexing. This is because
// vertex indexing means each vertex can only have one normal for all uses of that vertex (e.g. smooth faces).
// You can have vertex normals with indexing, but that involves unpacking the vertices and
// essentially not using indexing, meaning that the index system's overhead still exists
// without its functionality being used.
class Mesh {
private:
	std::vector<GameObject*> instances; // a vector of pointers to GameObjects that use this mesh
	Book<Mesh>::size_type selfIndex;	// this mesh's index in the book of all meshes
	
	Book<float>* vertexBook; // the book containing the vertices of this mesh
	Book<float>* normalBook; // the book containing the normals of this mesh
	Book<float>::size_type  vertexIndex; // the index of this mesh's first vertex in the vertexBook
	Book<float>::size_type  normalIndex; // the index of this mesh's first normal in the normalBook
	Book<float>::size_type  numVertices; // the number of vertices/normals that this mesh has
	float scale; // scalar to multiply all vertices by for rendering, etc.
	std::string name;
	Mesh() :
		selfIndex(0), vertexBook(0), normalBook(0), vertexIndex(0), normalIndex(0), numVertices(0), scale(1.0f), name("") {}
	Mesh(Book<Mesh>::size_type index, Book<float>* vb, Book<float>* nb, 
		 Book<int>::size_type vi, Book<int>::size_type ni,
		 unsigned int num, std::string meshName) : 
			selfIndex(index), vertexBook(vb), normalBook(nb), vertexIndex(vi), normalIndex(ni),
			numVertices(num), scale(1.0f), name(meshName) {}
public:
	Book<Mesh>::size_type getIndex() const;
	Book<float>::size_type getNumVertices() const;
	Vector3 getVertex(unsigned int i) const;
	Vector3 getNormal(unsigned int i) const;
	float getScale() const;
	void setScale(float newScale);
	
	friend class GraphicsInterface;
	friend class Book<Mesh>;
};

inline Book<Mesh>::size_type Mesh::getIndex() const
{
	return selfIndex;
}

inline Book<int>::size_type Mesh::getNumVertices() const
{
	return numVertices;
}

inline float Mesh::getScale() const
{
	return scale;
}

inline void Mesh::setScale(float newScale)
{
	scale = newScale;
}

inline Vector3 Mesh::getVertex(unsigned int i) const
{
	return Vector3(	(*vertexBook)[vertexIndex + 3 * i],
					(*vertexBook)[vertexIndex + 3 * i + 1],
					(*vertexBook)[vertexIndex + 3 * i + 2]);
}

inline Vector3 Mesh::getNormal(unsigned int i) const
{
	return Vector3(	(*normalBook)[normalIndex + 3 * i],
					(*normalBook)[normalIndex + 3 * i + 1],
					(*normalBook)[normalIndex + 3 * i + 2]);
}
	
}

#endif