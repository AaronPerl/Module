#ifndef __MODULE_POLYGONCONTAINER_HPP__
#define __MODULE_POLYGONCONTAINER_HPP__

#include <stdint.h>
#include <EASTL/vector.h>
#include "Vector3.hpp"
#include "Color.hpp"
#include "Book.hpp"

namespace Module {

// A class that stores a container of coordinates that form vertices, making up triangles
// It also stores a container of Polygon objects, which it uses to keep track of which polygons each vertex belongs to.
// This allows for easy movement and deletion of polygons, while still being able to keep track of 
class PolygonContainer {
private:
	eastl::vector<float> coordinates;
	eastl::vector<uint8_t> colors;
	//eastl::vector<Module::Polygon> polygons;
	Book<PolygonContainer>::size_type index;
	bool resized;
	bool updated;
	
	PolygonContainer()
		: index(0), resized(false), updated(false) {}
	PolygonContainer(Book<PolygonContainer>* parent, Book<PolygonContainer>::size_type parentIndex)
		: index(parentIndex), resized(false), updated(false) {}
public:
	typedef eastl::vector<float>::size_type size_type;
	
	// Adds a triangle, with its vertices arranged in counter-clockwise order
	void addTriangle(const Vector3& a, const Vector3& b, const Vector3& c, const Color& color)
	{
		resized = true;
		coordinates.push_back(a.getX());
		coordinates.push_back(a.getY());
		coordinates.push_back(a.getZ());
		coordinates.push_back(b.getX());
		coordinates.push_back(b.getY());
		coordinates.push_back(b.getZ());
		coordinates.push_back(c.getX());
		coordinates.push_back(c.getY());
		coordinates.push_back(c.getZ());
		colors.push_back(color.getRed());
		colors.push_back(color.getGreen());
		colors.push_back(color.getBlue());
		colors.push_back(color.getRed());
		colors.push_back(color.getGreen());
		colors.push_back(color.getBlue());
		colors.push_back(color.getRed());
		colors.push_back(color.getGreen());
		colors.push_back(color.getBlue());
		//polygons.push_back(Module::Polygon(3));
	}

	const eastl::vector<float>& getCoordinates() const { return coordinates; }
	const eastl::vector<uint8_t>& getColorComponents() const { return colors; }
	const size_type numTriangles() const { return coordinates.size() / 9; }
	const size_type numVertices() const { return coordinates.size() / 3; }
	Book<PolygonContainer*>::size_type getIndex() const { return index; }
	
	// Sets the coordinates of a face's vertex to a new value
	void setVertex(size_type faceIndex, short vertex, const Vector3& newValue)
	{
		updated = true;
		size_type startIndex = faceIndex * 9 + vertex * 3;
		coordinates[startIndex + 0] = newValue.getX();
		coordinates[startIndex + 1] = newValue.getY();
		coordinates[startIndex + 2] = newValue.getZ();
	}
	
	void setVertexColor(size_type faceIndex, short vertex, const Color& newColor)
	{
		updated = true;
		size_type startIndex = faceIndex * 9 + vertex * 3;
		colors[startIndex + 0] = newColor.getRed();
		colors[startIndex + 0] = newColor.getGreen();
		colors[startIndex + 0] = newColor.getBlue();
	}
	
	bool wasUpdated() { return updated; }
	bool wasResized() { return resized; }
	void resetUpdates() { updated = resized = false; }
	
	friend class GraphicsInterface;
	friend class Book<PolygonContainer>;
};

}

#endif