#ifndef __MODULE__GRAPHICSCALLBACK_HPP__
#define __MODULE__GRAPHICSCALLBACK_HPP__

namespace Module {

class GraphicsContext;

// An abstract class to hook into events triggered by the GraphicsInterface, such as pre-render, post-render, etc.
// Extend this class if you need to process these events.
class GraphicsCallback {
private:
public:
	/**
	 * Called at the beginning of a render cycle, before any objects are drawn.
	 * @param context A GraphicsContext object associated with the GraphicsInterface that called this hook.
	 */
	virtual void onPreRender(const GraphicsContext& context) {}
	
	/**
	 * Called at the end of a render cycle, after the world has been drawn, but before buffers have been swapped.
	 * @param context A GraphicsContext object associated with the GraphicsInterface that called this hook.
	 */
	virtual void onPostRender(const GraphicsContext& context) {}
};

}

#endif