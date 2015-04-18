#ifndef __SDLOPENGLINTERFACE_HPP__
#define __SDLOPENGLINTERFACE_HPP__

#include <ModuleGame.hpp>
#include <GraphicsInterface.hpp>
#include <GL/glew.h>

namespace Module
{
	class SDLOpenGLInterface : public GraphicsInterface
	{
		protected:
			void createWindow();
			void renderFrame();
			unsigned long getMilliseconds();
		public:
			SDLOpenGLInterface();
			
	};
}

#endif