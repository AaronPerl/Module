#include "GraphicsInterface.hpp"
#include "ModuleGame.hpp"
#include "Mesh.hpp"
#include "Vector3.hpp"

#include <cassert>

using namespace Module;

GraphicsInterface::GraphicsInterface() : fps(60), game(NULL), camera(NULL) {}

GraphicsInterface::GraphicsInterface(unsigned int set_fps) : fps(set_fps), game(NULL), camera(NULL) {}

void GraphicsInterface::start()
{
	game->startThread(this);
}

void GraphicsInterface::run()
{
	unsigned long prevTime = getMilliseconds();
	createWindow();
	while (1)
	{
		renderFrame();
		while (getMilliseconds() - prevTime < 1000/fps);
	}
}

Mesh* GraphicsInterface::createMesh(Vector3* vertices, Vector3* normals, unsigned int num_vertices, const std::string& name)
{
	assert(num_vertices);
	Book<Vector3>::size_type firstIndex = allVertices.size();
	for (unsigned int i = 0; i < num_vertices; i++)
	{
		allVertices.push_back(vertices[i].getX());
		allVertices.push_back(vertices[i].getY());
		allVertices.push_back(vertices[i].getZ());
		allNormals.push_back(normals[i].getX());
		allNormals.push_back(normals[i].getY());
		allNormals.push_back(normals[i].getZ());
	}
	allMeshes.push_back(Mesh(&allVertices, &allNormals, firstIndex, firstIndex, num_vertices, name));
	return &allMeshes.back();
}

Mesh* GraphicsInterface::createMesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::string& name)
{
	Book<Vector3>::size_type firstIndex = allVertices.size();
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		allVertices.push_back(vertices[i].getX());
		allVertices.push_back(vertices[i].getY());
		allVertices.push_back(vertices[i].getZ());
		allNormals.push_back(normals[i].getX());
		allNormals.push_back(normals[i].getY());
		allNormals.push_back(normals[i].getZ());
	}
	allMeshes.push_back(Mesh(&allVertices, &allNormals, firstIndex, firstIndex, vertices.size(), name));
	return &allMeshes.back();
}


/*Mesh* GraphicsInterface::copyMesh(Mesh* other)
{
	return createMesh(other->vertices, other->normals, other->numVertices, other->name); // won't work given vertices may not be contiguous (across 2 or more pages)
}*/

