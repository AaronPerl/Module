#ifndef __MODULE__GRAPHICSCALLBACK_HPP__
#define __MODULE__GRAPHICSCALLBACK_HPP__

namespace Module {

class GraphicsContext;

// An abstract class to hook into events triggered by the GraphicsInterface, such as pre-render, post-render, etc.
// Extend this class if you need to process these events.
class GraphicsCallback {
private:
public:
	virtual void onPreRender(const GraphicsContext& context) {}
	virtual void onPostRender(const GraphicsContext& context) {}
};

}

#endif