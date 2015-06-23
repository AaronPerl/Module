#ifndef __MODULE__GRAPHICSCCONTEXT_HPP__
#define __MODULE__GRAPHICSCCONTEXT_HPP__

namespace Module {

// A class that provides acccess to private members of a GraphicsInterface, used in conjunction with GraphicsCallbacks.
class GraphicsContext {
private:
	GraphicsInterface* interface;
	GraphicsContext(GraphicsInterface* gInterface)
	{
		interface = gInterface;
	}
public:
	void drawPolygons2D(const PolygonContainer& polygons) { interface->drawPolygons2D(polygons); }
	
	friend class GraphicsInterface;
};

}

#endif