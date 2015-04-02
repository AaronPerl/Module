#include "GraphicsInterface.hpp"
#include "Mesh.hpp"
#include "Vector3.hpp"

#include <cassert>

using namespace Module;

GraphicsInterface::GraphicsInterface() : fps(60) {}

GraphicsInterface::GraphicsInterface(unsigned int set_fps) : fps(set_fps) {}

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

Mesh* GraphicsInterface::createMesh(Vector3* vertices, unsigned int num_vertices, const std::string& name)
{
	assert(num_vertices);
	DynamicArray<Vector3>::size_type firstIndex = allVertices.size();
	allVertices.append(vertices, num_vertices);
	Mesh* retVal = new Mesh(&allVertices[firstIndex], num_vertices, name);
	return retVal;
}

Mesh* GraphicsInterface::createMesh(const DynamicArray<Vector3>& vertices, const std::string& name)
{
	DynamicArray<Vector3>::size_type firstIndex = allVertices.size();
	allVertices.append(vertices);
	Mesh* retVal = new Mesh(&allVertices[firstIndex], vertices.size(), name);
	return retVal;
}


/*Mesh* GraphicsInterface::copyMesh(Mesh* other)
{

	Mesh* retVal = new Mesh();
	return retVal;
}*/

