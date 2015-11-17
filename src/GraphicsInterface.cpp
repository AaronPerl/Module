#include "GraphicsInterface.hpp"
#include "Book.hpp"
#include "Vector3.hpp"
#include "InputCallback.hpp"
#include "GraphicsCallback.hpp"
#include "GraphicsContext.hpp"
#include "ModuleGame.hpp"

#include <cassert>

using namespace Module;

GraphicsInterface::GraphicsInterface() : fps(60), game(NULL), camera(NULL)
{
	for (unsigned int i = 0; i < sizeof(keyStates)/sizeof(bool); i++)
	{
		keyStates[i] = false;
	}
}

GraphicsInterface::GraphicsInterface(unsigned int set_fps) : fps(set_fps), game(NULL), camera(NULL) {}

void GraphicsInterface::start()
{
	game->startThread(this);
}

void GraphicsInterface::run()
{
	// unsigned long prevTime = getMilliseconds();
	createWindow();
	while (isRunning())
	{
		preRender();
		renderFrame();
		postRender();
		swapBuffers();
		// while (getMilliseconds() - prevTime < 1000.0/fps);
		// prevTime = getMilliseconds();
	}
}

void GraphicsInterface::preRender()
{
	GraphicsContext context(this);
	for (unsigned int i = 0; i < graphicsCallbacks.size(); i++)
	{
		graphicsCallbacks[i]->onPreRender(context);
	}
}

void GraphicsInterface::postRender()
{
	GraphicsContext context(this);
	for (unsigned int i = 0; i < graphicsCallbacks.size(); i++)
	{
		graphicsCallbacks[i]->onPostRender(context);
	}
}

void GraphicsInterface::mousePressed(uint8_t button, uint16_t x, uint16_t y)
{
	for (unsigned int i = 0; i < inputCallbacks.size(); i++)
	{
		inputCallbacks[i]->onMouseDown(button, x, y);
	}
}

void GraphicsInterface::mouseReleased(uint8_t button, uint16_t x, uint16_t y)
{
	for (unsigned int i = 0; i < inputCallbacks.size(); i++)
	{
		inputCallbacks[i]->onMouseUp(button, x, y);
	}
}

void GraphicsInterface::mouseMoved(uint16_t x, uint16_t y, int16_t dx, int16_t dy)
{
	for (unsigned int i = 0; i < inputCallbacks.size(); i++)
	{
		inputCallbacks[i]->onMouseMove(x,y,dx,dy);
	}
}

void GraphicsInterface::keyPressed(KeyCode::Code code, char keyChar)
{
	keyStates[code] = true;
	for (unsigned int i = 0; i < inputCallbacks.size(); i++)
	{
		inputCallbacks[i]->onKeyDown(code, keyChar);
	}
}

void GraphicsInterface::keyReleased(KeyCode::Code code, char keyChar)
{
	keyStates[code] = false;
	for (unsigned int i = 0; i < inputCallbacks.size(); i++)
	{
		inputCallbacks[i]->onKeyUp(code, keyChar);
	}
}

Mesh* GraphicsInterface::createMesh(Vector3* vertices, Vector3* normals, float* uvs, unsigned int num_vertices, const std::string& name)
{
	assert(num_vertices);
	Book<float>::size_type firstIndex = allVertices.size();
	Book<float>::size_type firstUVIndex = allUVs.size();
	for (unsigned int i = 0; i < num_vertices; i++)
	{
		allVertices.push_back(vertices[i].getX());
		allVertices.push_back(vertices[i].getY());
		allVertices.push_back(vertices[i].getZ());
		allNormals.push_back(normals[i].getX());
		allNormals.push_back(normals[i].getY());
		allNormals.push_back(normals[i].getZ());
		if (uvs != 0)
		{
			allUVs.push_back(uvs[2 * i]);
			allUVs.push_back(uvs[2 * i + 1]);
		}
	}
	allMeshes.push_back(Mesh(allMeshes.size(), &allVertices, &allNormals, &allUVs, uvs != 0, firstIndex, firstIndex, firstUVIndex, num_vertices, name));
	return &allMeshes.back();
}

Mesh* GraphicsInterface::createMesh(const std::vector<Vector3>& vertices, const std::vector<Vector3>& normals, const std::vector<float>& uvs, 
                                    const std::string& name)
{
	Book<float>::size_type firstIndex = allVertices.size();
	Book<float>::size_type firstUVIndex = allUVs.size();
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		allVertices.push_back(vertices[i].getX());
		allVertices.push_back(vertices[i].getY());
		allVertices.push_back(vertices[i].getZ());
		allNormals.push_back(normals[i].getX());
		allNormals.push_back(normals[i].getY());
		allNormals.push_back(normals[i].getZ());
		if (uvs.size() > 0)
		{
			allUVs.push_back(uvs[2 * i]);
			allUVs.push_back(uvs[2 * i + 1]);
		}
	}
	allMeshes.push_back(Mesh(allMeshes.size(), &allVertices, &allNormals, &allUVs, uvs.size() > 0, firstIndex, firstIndex, firstUVIndex, vertices.size(), name));
	return &allMeshes.back();
}


/*Mesh* GraphicsInterface::copyMesh(Mesh* other)
{
	return createMesh(other->vertices, other->normals, other->numVertices, other->name); // won't work given vertices may not be contiguous (across 2 or more pages)
}*/

PolygonContainer* GraphicsInterface::createPolygonContainer()
{
	unsigned int index = allPolygons.size();
	allPolygons.push_back(PolygonContainer(&allPolygons, index));
	return &allPolygons.back();
}

void GraphicsInterface::addGraphicsCallback(GraphicsCallback* callback)
{
	graphicsCallbacks.push_back(callback);
}

void GraphicsInterface::addInputCallback(InputCallback* callback)
{
	inputCallbacks.push_back(callback);
}

