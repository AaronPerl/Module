#ifndef __MODULE__GRAPHICSCCONTEXT_HPP__
#define __MODULE__GRAPHICSCCONTEXT_HPP__

#include "ModuleDefines.hpp"

namespace Module {

// A class that provides acccess to private members of a GraphicsInterface, used in conjunction with GraphicsCallbacks.
class GraphicsContext {
private:
	GraphicsInterface* graphics;
	GraphicsContext(GraphicsInterface* gInterface)
	{
		graphics = gInterface;
	}
public:
	void drawPolygons2D(const PolygonContainer& polygons) { graphics->drawPolygons2D(polygons); }
	
	friend class GraphicsInterface;
};

}

#endif